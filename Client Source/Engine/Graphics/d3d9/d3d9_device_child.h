#pragma once

#include "d3d9_include.h"
#include "d3d9_devref_tracker.h"

namespace dxvk {

  class D3D9DeviceEx;

  // Helper to get a human-readable name for the COM interface type
  // (works at compile time via template specialization)
  template<typename T> struct D3D9TypeName { static const char* Get() { return "Unknown"; } };
  template<> struct D3D9TypeName<IDirect3DVertexBuffer9>      { static const char* Get() { return "VertexBuffer"; } };
  template<> struct D3D9TypeName<IDirect3DIndexBuffer9>       { static const char* Get() { return "IndexBuffer"; } };
  template<> struct D3D9TypeName<IDirect3DVertexShader9>      { static const char* Get() { return "VertexShader"; } };
  template<> struct D3D9TypeName<IDirect3DPixelShader9>       { static const char* Get() { return "PixelShader"; } };
  template<> struct D3D9TypeName<IDirect3DVertexDeclaration9> { static const char* Get() { return "VertexDeclaration"; } };
  template<> struct D3D9TypeName<IDirect3DSurface9>           { static const char* Get() { return "Surface"; } };
  template<> struct D3D9TypeName<IDirect3DTexture9>           { static const char* Get() { return "Texture"; } };
  template<> struct D3D9TypeName<IDirect3DCubeTexture9>       { static const char* Get() { return "CubeTexture"; } };
  template<> struct D3D9TypeName<IDirect3DVolumeTexture9>     { static const char* Get() { return "VolumeTexture"; } };
  template<> struct D3D9TypeName<IDirect3DSwapChain9>         { static const char* Get() { return "SwapChain"; } };
  template<> struct D3D9TypeName<IDirect3DSwapChain9Ex>       { static const char* Get() { return "SwapChainEx"; } };
  template<> struct D3D9TypeName<IDirect3DStateBlock9>        { static const char* Get() { return "StateBlock"; } };
  template<> struct D3D9TypeName<IDirect3DQuery9>             { static const char* Get() { return "Query"; } };
  template<> struct D3D9TypeName<IDirect3DVolume9>            { static const char* Get() { return "Volume"; } };

  template <typename Base>
  class D3D9DeviceChild : public ComObjectClamp<Base> {

  public:

    D3D9DeviceChild(D3D9DeviceEx* pDevice)
      : m_parent( pDevice ) { }

    ULONG STDMETHODCALLTYPE AddRef() {
      uint32_t refCount = this->m_refCount++;
      if (unlikely(!refCount)) {
        this->AddRefPrivate();
        GetDevice()->AddRef();
        D3D9_DEVREF_TRACK_ADD(this, D3D9TypeName<Base>::Get());
      }

      return refCount + 1;
    }

    ULONG STDMETHODCALLTYPE Release() {
      uint32_t refCount = --this->m_refCount;
      if (unlikely(!refCount)) {
        D3D9_DEVREF_TRACK_REMOVE(this, D3D9TypeName<Base>::Get());
        auto* pDevice = GetDevice();
        this->ReleasePrivate();
        pDevice->Release();
      }
      return refCount;
    }

    HRESULT STDMETHODCALLTYPE GetDevice(IDirect3DDevice9** ppDevice) {
      InitReturnPtr(ppDevice);

      if (ppDevice == nullptr)
        return D3DERR_INVALIDCALL;

      *ppDevice = ref(GetDevice());
      return D3D_OK;
    }

    IDirect3DDevice9Ex* GetDevice() {
      return reinterpret_cast<IDirect3DDevice9Ex*>(m_parent);
    }

    D3D9DeviceEx* GetParent() {
      return m_parent;
    }

  protected:

    D3D9DeviceEx* m_parent;

  };

}