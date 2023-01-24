#include "Renderer.h"

#include <Logger/Logger.h>

Engine::Renderer::Renderer()
{
}

Engine::Renderer::~Renderer()
{
    m_Device.Reset();
    m_SwapChain.Reset();
    m_Context.Reset();
    m_InputLayout.Reset();
    m_RenderTargetView.Reset();
}

bool Engine::Renderer::Initialize(HWND handle)
{
    ComPtr<ID3DBlob> Blob;

    if (!CreateDeviceContext())
        return false;
    if (!CreateSwapChain(handle))
        return false;
    if (!CreateRenderTargetView())
        return false;
    if (!CreatePixelShader(Blob))
        return false;
    if (!CreateVertexShader(Blob))
        return false;
    if (!CreateInputLayout(Blob))
        return false;

    return true;
}

bool Engine::Renderer::CreateDeviceContext(DriverTypes typeValue)
{
    D3D_DRIVER_TYPE driverType{};

    switch (typeValue)
    {
    case DriverTypes::Hardware:
        driverType = D3D_DRIVER_TYPE_HARDWARE;
        break;
    case DriverTypes::Software:
        driverType = D3D_DRIVER_TYPE_SOFTWARE;
        break;
    case DriverTypes::Reference:
        driverType = D3D_DRIVER_TYPE_REFERENCE;
        break;
    case DriverTypes::Warp:
        driverType = D3D_DRIVER_TYPE_WARP;
        break;
    default:
        driverType = D3D_DRIVER_TYPE_HARDWARE;
        break;
    }

    HRESULT hr = D3D11CreateDevice(nullptr, driverType, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION,
                                   m_Device.GetAddressOf(), nullptr, m_Context.GetAddressOf());
    if (FAILED(hr))
    {
        CONSOLE_LOG(Warning, "Failed to create the D3D11 Device.\n");
        return false;
    }
    CONSOLE_LOG(Success, "D3D11 Device has been successfuly created.\n");

    return EXIT_SUCCESS;
}

bool Engine::Renderer::CreateSwapChain(HWND handle)
{
    return false;
}

bool Engine::Renderer::CreateRenderTargetView()
{
    return false;
}

bool Engine::Renderer::CreatePixelShader(ComPtr<ID3DBlob> &Blob)
{
    return false;
}

bool Engine::Renderer::CreateVertexShader(ComPtr<ID3DBlob> &Blob)
{
    return false;
}

bool Engine::Renderer::CreateInputLayout(ComPtr<ID3DBlob> &Blob)
{
    return false;
}

void Engine::Renderer::UpdateFrame()
{
}

void Engine::Renderer::ClearFrame()
{
}
