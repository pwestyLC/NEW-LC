#pragma once

#include <fstream>
#include <optional>
#include <chrono>
#include <d3dx9.h>

namespace ShaderManager
{
    struct VertexShaderData
    {
        IDirect3DVertexShader9* shader;
        IDirect3DVertexDeclaration9* declaration;
        ID3DXConstantTable* constantTable;
    };

    struct PixelShaderData
    {
        IDirect3DPixelShader9* shader;
        ID3DXConstantTable* constantTable;
    };

    /**
     * @brief Stores a vertex shader and its declaration.
     *
     * @param pVertexShader Pointer to the vertex shader to store.
     * @param pVertexDeclaration Pointer to the vertex declaration to store.
     * @param pConstantTable Pointer to the constant table.
     * @return DWORD A handle to the stored vertex shader.
     */
    DWORD StoreVertexShader(IDirect3DVertexShader9* pVertexShader, IDirect3DVertexDeclaration9* pVertexDeclaration, ID3DXConstantTable* pConstantTable = nullptr);

    /**
     * @brief Deletes a vertex shader by releasing its resources and clearing its entry.
     *
     * @param dwHandle The handle (index) of the vertex shader to delete.
     * @return true if the shader was deleted successfully, false otherwise.
     */
    bool DeleteVertexShader(DWORD dwHandle);

    /**
     * @brief Retrieves a vertex shader based on its handle.
     *
     * @param dwHandle The handle (index) of the vertex shader.
     * @return A pointer to the VertexShaderData struct containing the shader, or nullptr if the handle is invalid.
     */
    VertexShaderData* GetVertexShader(DWORD dwHandle);

    /**
     * @brief Sets the current vertex shader.
     *
     * @param dwHandle The handle of the vertex shader to set.
     */
    void SetVertexShader(DWORD dwHandle);

    /**
     * @brief Sets a constant value for a vertex shader.
     * 
     * @param dwHandle The handle of the vertex shader.
     * @param constantName The name of the constant in the shader.
     * @param data Pointer to the data to set.
     * @param vectorCount The number of 4-component vectors to set.
     */
    void SetVertexShaderConstant(DWORD dwHandle, const char* constantName, const void* data, UINT vectorCount);

    /**
     * @brief Stores a pixel shader.
     *
     * @param pPixelShader Pointer to the pixel shader to store.
     * @param pConstantTable Pointer to the constant table.
     * @return DWORD A handle to the stored pixel shader.
     */
    DWORD StorePixelShader(IDirect3DPixelShader9* pPixelShader, ID3DXConstantTable* pConstantTable = nullptr);

    /**
     * @brief Deletes a pixel shader by releasing its resources and clearing its entry.
     *
     * @param dwHandle The handle (index) of the pixel shader to delete.
     * @return true if the shader was deleted successfully, false otherwise.
     */
    bool DeletePixelShader(DWORD dwHandle);

    /**
     * @brief Retrieves a pixel shader based on its handle.
     *
     * @param dwHandle The handle (index) of the pixel shader.
     * @return A pointer to the PixelShaderData struct containing the shader, or nullptr if the handle is invalid.
     */
    PixelShaderData* GetPixelShader(DWORD dwHandle);

    /**
     * @brief Sets the current pixel shader.
     *
     * @param dwHandle The handle of the pixel shader to set.
     */
    void SetPixelShader(DWORD dwHandle);

    /**
     * @brief Sets a constant value for a pixel shader.
     *
     * @param dwHandle The handle of the pixel shader.
     * @param constantName The name of the constant in the shader.
     * @param data Pointer to the data to set.
     * @param vectorCount The number of 4-component vectors to set.
     */
    void SetPixelShaderConstant(DWORD dwHandle, const char* constantName, const void* data, UINT vectorCount);

    /**
     * @brief Compiles a shader from source code.
     *
     * @param shaderSource The source code of the shader.
     * @param entryPoint The entry point function of the shader.
     * @param shaderModel The shader model version (e.g., "vs_2_0", "ps_2_0").
     * @param pShaderBuffer A pointer to the compiled shader buffer.
     * @param ppConstantTable A pointer to receive the constant table.
     * @return HRESULT status code. S_OK if successful, otherwise an error code.
     *
     * @note Error messages, if any, are logged to a file and output to the debug console.
     */
    HRESULT CompileShader(const std::string& shaderSource, const std::string& entryPoint, const char* shaderModel, ID3DXBuffer** ppShaderBuffer, ID3DXConstantTable** ppConstantTable = nullptr);
    
    /**
     * @brief Compiles a shader from a file.
     *
     * @param filePath The file path of the shader to compile, relative to the main client directory.
     * @param entryPoint The entry point function of the shader.
     * @param shaderModel The shader model version (e.g., "vs_2_0", "ps_2_0").
     * @param pShaderBuffer A pointer to the compiled shader buffer.
     * @param ppConstantTable A pointer to receive the constant table.
     * @return HRESULT status code. S_OK if successful, otherwise an error code.
     *
     * @note Error messages, if any, are logged to a file and output to the debug console.
     * @details Reads the shader from the file and compiles it. Logs any errors to a file and outputs them to the debug console.
     */
    HRESULT CompileShaderFromFile(std::string filePath, const std::string& entryPoint, const char* shaderModel, ID3DXBuffer** pShaderBuffer, ID3DXConstantTable** ppConstantTable = nullptr);
    
    /**
     * @brief Assembles a shader from assembly code.
     *
     * @param shaderSource The assembly code of the shader.
     * @param shaderModel The shader model version (e.g., "vs_1_1", "ps_1_4").
     * @param ppShaderBuffer A pointer to receive the assembled shader buffer.
     * @return HRESULT status code. S_OK if successful, otherwise an error code.
     * 
     * @note Error messages, if any, are logged to a file and output to the debug console.
     */
    HRESULT AssembleShader(const std::string& shaderSource, const char* shaderModel, ID3DXBuffer** ppShaderBuffer);

    /**
     * @brief Logs shader compilation or assembly errors to a file and outputs them to the debug console.
     *
     * @param shaderSource The source code of the shader (optional).
     * @param entryPoint The entry point function of the shader (optional).
     * @param shaderModel The shader model version (optional).
     * @param errorMessage The error message generated during shader compilation or assembly.
     */
    void LogShaderError(const std::optional<std::string>& shaderSource, const std::optional<std::string>& entryPoint, const char* shaderModel, const std::string& errorMessage);

    /**
     * @brief Releases all stored shaders and their associated resources.
     */
    void Release();
}
