#include "StdH.h"

#include <filesystem>

#include <Engine/Base/Stream.h>
#include <Engine/Graphics/GfxLibrary.h>
#include <Engine/Graphics/ShaderManager.h>

namespace ShaderManager
{
    /// @brief A list of vertex shaders
    std::unordered_map<DWORD, VertexShaderData*> vertexShaders(0);

    /// @brief A list of pixel shaders
    std::unordered_map<DWORD, PixelShaderData*> pixelShaders(0);

    /// @brief Current vertex shader handle.
    DWORD currentVertexShaderHandle = 0;

    /// @brief Current pixel shader handle.
    DWORD currentPixelShaderHandle = 0;

    /// @brief Enables debug information when compiling shaders.
    constexpr bool bEnableShaderDebug = true;

    /// @brief Disables shader validation during the compilation process.
    constexpr bool bDisableShaderValidation = false;

    /// @brief Enables logging of shader source code in case of compilation errors.
    constexpr bool bShowShaderSourceInLog = true;

    DWORD StoreVertexShader(IDirect3DVertexShader9* pVertexShader, IDirect3DVertexDeclaration9* pVertexDeclaration, ID3DXConstantTable* pConstantTable)
    {
        auto pVertexShaderData = new VertexShaderData();
        pVertexShaderData->shader = pVertexShader;
        pVertexShaderData->declaration = pVertexDeclaration;
        pVertexShaderData->constantTable = pConstantTable;

        // since VertexShaderData is at least 8 byte aligned, we can safely shift it to right and end up not overwriting the top bit
        const DWORD dwShaderMagic = reinterpret_cast<DWORD>(pVertexShaderData) >> 1;
        const DWORD dwHandle = dwShaderMagic | 0x80000000;

        vertexShaders[dwHandle] = pVertexShaderData;

        return dwHandle;
    }

    bool DeleteVertexShader(DWORD dwHandle)
    {
        const bool isFlexible = (dwHandle & 0x80000000) == 0;

        if (isFlexible)
            return false;

        auto pVertexShaderData = GetVertexShader(dwHandle);

        if (currentVertexShaderHandle == dwHandle)
            SetVertexShader(NULL);

        if (pVertexShaderData->shader)
            pVertexShaderData->shader->Release();

        if (pVertexShaderData->declaration)
            pVertexShaderData->declaration->Release();

        vertexShaders.erase(dwHandle);
        return true;
    }

    VertexShaderData* GetVertexShader(DWORD dwHandle)
    {
        const DWORD handleMagic = dwHandle << 1;
        const auto data = reinterpret_cast<ShaderManager::VertexShaderData*>(handleMagic);

        return data;
    }

    void SetVertexShader(DWORD dwHandle)
    {
        const bool isFlexible = (dwHandle & 0x80000000) == 0;

        if (isFlexible)
        {
            _pGfx->gl_pd3dDevice->SetVertexShader(nullptr);
            _pGfx->gl_pd3dDevice->SetFVF(dwHandle);

            currentVertexShaderHandle = 0;
            return;
        }

        const DWORD handleMagic = dwHandle << 1;
        const auto data = reinterpret_cast<ShaderManager::VertexShaderData*>(handleMagic);

        if (data) {
            _pGfx->gl_pd3dDevice->SetVertexShader(data->shader);
            _pGfx->gl_pd3dDevice->SetVertexDeclaration(data->declaration);
        }

        currentVertexShaderHandle = dwHandle;
    }

    void SetVertexShaderConstant(DWORD dwHandle, const char* constantName, const void* data, UINT vectorCount)
    {
        auto pVertexShaderData = GetVertexShader(dwHandle);
        if (pVertexShaderData && pVertexShaderData->constantTable) {
            pVertexShaderData->constantTable->SetFloatArray(_pGfx->gl_pd3dDevice, constantName, static_cast<const float*>(data), vectorCount);
        }
    }

    void SetPixelShader(DWORD dwHandle)
    {
        const auto data = reinterpret_cast<ShaderManager::PixelShaderData*>(dwHandle);
        _pGfx->gl_pd3dDevice->SetPixelShader(data ? data->shader : nullptr);
        currentPixelShaderHandle = dwHandle;
    }

    void SetPixelShaderConstant(DWORD dwHandle, const char* constantName, const void* data, UINT vectorCount)
    {
        auto pPixelShaderData = GetPixelShader(dwHandle);

        if (pPixelShaderData && pPixelShaderData->constantTable) {
            pPixelShaderData->constantTable->SetFloatArray(_pGfx->gl_pd3dDevice, constantName, static_cast<const float*>(data), vectorCount);
        }
    }

    DWORD StorePixelShader(IDirect3DPixelShader9* pPixelShader, ID3DXConstantTable* pConstantTable)
    {
        auto pPixelShaderData = new PixelShaderData();
        pPixelShaderData->shader = pPixelShader;
        pPixelShaderData->constantTable = pConstantTable;

        const DWORD dwHandle = reinterpret_cast<DWORD>(pPixelShaderData);
        pixelShaders[dwHandle] = pPixelShaderData;

        return dwHandle;
    }

    bool DeletePixelShader(DWORD dwHandle)
    {
        if (currentPixelShaderHandle == dwHandle)
            SetPixelShader(NULL);

        auto pPixelShaderData = GetPixelShader(dwHandle);

        if (!pPixelShaderData->shader)
            return false;

        pPixelShaderData->shader->Release();
        pixelShaders.erase(dwHandle);

        return true;
    }

    PixelShaderData* GetPixelShader(DWORD dwHandle)
    {
        const auto pPixelShaderData = reinterpret_cast<ShaderManager::PixelShaderData*>(dwHandle);
        return pPixelShaderData;
    }

    HRESULT CompileShader(const std::string& shaderSource, const std::string& entryPoint, const char* shaderModel, ID3DXBuffer** ppShaderBuffer, ID3DXConstantTable** ppConstantTable)
    {
        DWORD dwShaderFlags = NULL;
        ID3DXBuffer* pErrorBuffer = nullptr;

        if (bDisableShaderValidation)
            dwShaderFlags |= D3DXSHADER_SKIPVALIDATION;

        if (bEnableShaderDebug)
            dwShaderFlags |= D3DXSHADER_DEBUG;

        HRESULT hr;

        hr = D3DXCompileShader(
            shaderSource.c_str(),
            shaderSource.size(),
            nullptr,
            nullptr,
            entryPoint.c_str(),
            shaderModel,
            dwShaderFlags,
            ppShaderBuffer,
            &pErrorBuffer,
            ppConstantTable 
        );

        if (FAILED(hr) || pErrorBuffer) {
            LogShaderError(shaderSource, entryPoint, shaderModel, static_cast<const char*>(pErrorBuffer->GetBufferPointer()));
            OutputDebugStringA(static_cast<const char*>(pErrorBuffer->GetBufferPointer()));
            pErrorBuffer->Release();

            return hr;
        }

        return S_OK;
    }

    HRESULT AssembleShader(const std::string& shaderSource, const char* shaderModel, ID3DXBuffer** ppShaderBuffer)
    {
        DWORD dwShaderFlags = NULL;
        ID3DXBuffer* pErrorBuffer = nullptr;

        if (bDisableShaderValidation)
            dwShaderFlags |= D3DXSHADER_SKIPVALIDATION;

        if (bEnableShaderDebug)
            dwShaderFlags |= D3DXSHADER_DEBUG;

        HRESULT hr;

        hr = D3DXAssembleShader(
            shaderSource.c_str(),
            shaderSource.size(),
            nullptr,
            nullptr,
            dwShaderFlags,
            ppShaderBuffer,
            &pErrorBuffer
        );

        if (FAILED(hr) || pErrorBuffer) {
            LogShaderError(shaderSource, std::nullopt, shaderModel, static_cast<const char*>(pErrorBuffer->GetBufferPointer()));
            OutputDebugStringA(static_cast<const char*>(pErrorBuffer->GetBufferPointer()));
            pErrorBuffer->Release();

            return hr;
        }

        return S_OK;
    }

    HRESULT CompileShaderFromFile(std::string filePath, const std::string& entryPoint, const char* shaderModel, ID3DXBuffer** pShaderBuffer, ID3DXConstantTable** ppConstantTable)
    {
        filePath = _fnmApplicationPath.str_String + filePath;
        std::ifstream file(filePath, std::ios::binary | std::ios::ate);

        if (!file.is_open()) {
            return E_FAIL;
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<char> buffer(size);

        if (!file.read(buffer.data(), size)) {
            LogShaderError(std::nullopt, entryPoint, shaderModel, "Failed to read shader file: " + filePath);
            return E_FAIL;
        }

        std::string shaderSource(buffer.begin(), buffer.end());
        return CompileShader(shaderSource, entryPoint, shaderModel, pShaderBuffer, ppConstantTable);
    }

    void LogShaderError(const std::optional<std::string>& shaderSource, const std::optional<std::string>& entryPoint, const char* shaderModel, const std::string& errorMessage)
    {
        // create the logs directory if it doesn't exist
        std::filesystem::path logDir = std::filesystem::path(_fnmApplicationPath.str_String) / "Logs";
        std::filesystem::create_directories(logDir);

        std::ofstream logFile(logDir / "shaders-log.txt", std::ios::app);

        if (logFile.is_open())
        {
            auto now = std::chrono::system_clock::now();
            const time_t in_time_t = std::chrono::system_clock::to_time_t(now);

            std::stringstream ss;
            ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");

            logFile << "----------------------------------------" << std::endl;
            logFile << "timestamp: " << ss.str() << std::endl;

            if (entryPoint.has_value())
                logFile << "entry point: " << *entryPoint << std::endl;
            else
                logFile << "entry point: Not specified (ASM)" << std::endl;

            if (shaderModel)
                logFile << "version: " << shaderModel << std::endl;

            logFile << "message:" << std::endl;
            logFile << errorMessage << std::endl;
            logFile << "----------------------------------------" << std::endl << std::endl;

            if (bShowShaderSourceInLog && shaderSource.has_value()) {
                logFile << *shaderSource << std::endl;
                logFile << "----------------------------------------" << std::endl << std::endl;
            }

            logFile.close();
        }
        else {
            OutputDebugStringA("Failed to open shader compilation log file.\n");
        }

        // also output to debug console
        OutputDebugStringA(("Shader Compilation Error/Warning:\n" + errorMessage).c_str());
    }

    void Release()
    {
        for (const auto& [key, value] : vertexShaders)
        {
            if (value->shader)
                value->shader->Release();

            if (value->declaration)
                value->declaration->Release();

            if (value->constantTable)
                value->constantTable->Release();
        }

        vertexShaders.clear();

        for (const auto& [key, value] : pixelShaders)
        {
            if (value->shader)
                value->shader->Release();

            if (value->constantTable)
                value->constantTable->Release();
        }

        pixelShaders.clear();
    }
}
