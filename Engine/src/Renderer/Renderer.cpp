#include "Renderer.h"

#include <Logger/Logger.h>

Engine::Renderer::Renderer(int width, int height) : m_Device(nullptr), m_SwapChain(nullptr), m_Context(nullptr), m_RenderTargetView(nullptr)
{
	Viewport.Width = (float)width;
	Viewport.Height = (float)height;
	Viewport.MinDepth = 0;
	Viewport.MaxDepth = 1;
	Viewport.TopLeftX = 0;
	Viewport.TopLeftY = 0;
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
	ComPtr<ID3DBlob> Blob{};

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

	return true;
}

bool Engine::Renderer::CreateSwapChain(HWND handle)
{
	DXGI_SWAP_CHAIN_DESC SwapChainDesc{};

	//  Swap chain figures out the size of the window by checking window handle
	SwapChainDesc.BufferDesc.Width = (unsigned int)Viewport.Width;
	SwapChainDesc.BufferDesc.Height = (unsigned int)Viewport.Height;

	//  Color Format
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;

	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	//  Since we don't specify size, scaling is also unspecified.
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	//  Anti-aliasing
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;

	//  Pipeline is going to be rendering all of stuff.
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.BufferCount = 2;

	SwapChainDesc.OutputWindow = handle;
	SwapChainDesc.Windowed = true;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapChainDesc.Flags = 0;

	ComPtr<IDXGIDevice> dxgiDevice;

	HRESULT hr = m_Device.As(&dxgiDevice);
	if (FAILED(hr)) {
		CONSOLE_LOG(Error, "Failed to get the DXGI Device.");
		return false;
	}

	ComPtr<IDXGIAdapter> dxgiAdapter;

	hr = dxgiDevice.Get()->GetParent(IID_PPV_ARGS(dxgiAdapter.GetAddressOf()));

	if (FAILED(hr)) {
		CONSOLE_LOG(Error, "Failed to get the DXGI Adapter.");
		return false;
	}

	return false;
}

bool Engine::Renderer::CreateRenderTargetView()
{
	return false;
}

bool Engine::Renderer::CreatePixelShader(ComPtr<ID3DBlob>& Blob)
{
	return false;
}

bool Engine::Renderer::CreateVertexShader(ComPtr<ID3DBlob>& Blob)
{
	return false;
}

bool Engine::Renderer::CreateInputLayout(ComPtr<ID3DBlob>& Blob)
{
	return false;
}

void Engine::Renderer::UpdateFrame()
{
}

void Engine::Renderer::ClearFrame()
{
	const float clearColor[] = { 0.084f, 0.106f, 0.122, 1.0f };
	m_Context->ClearRenderTargetView(m_RenderTargetView.Get(), clearColor);
}
