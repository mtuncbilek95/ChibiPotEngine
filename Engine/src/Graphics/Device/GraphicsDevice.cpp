#include "GraphicsDevice.h"

#include <Logger/Logger.h>

Engine::GraphicsDevice::GraphicsDevice()
{
}

bool Engine::GraphicsDevice::Initialize(const HWND handle, int m_width, int m_height)
{
	if (!CreateDeviceContext())
		return false;
	if (!CreateSwapChain(handle))
		return false;
	if (!CreateViewport(m_width, m_height))
		return false;
	if (!CreateRenderTargetView())
		return false;

	

	return true;
}
bool Engine::GraphicsDevice::CreateDeviceContext(const DriverTypes driverValue, const FeatureTypesDX featureValue)
{
	D3D_DRIVER_TYPE driverType{};
	uint8 featureType{};

	switch (driverValue)
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

	switch (featureValue)
	{
	case FeatureTypesDX::Dx11:
		featureType = D3D11_SDK_VERSION;
		break;

	default:
		featureType = D3D11_SDK_VERSION;
		break;
	}

	HRESULT hr = D3D11CreateDevice(nullptr, driverType, nullptr, D3D11_CREATE_DEVICE_DEBUG, nullptr, 0, featureType,
								   m_Device.GetAddressOf(), nullptr, m_Context.GetAddressOf());
	if (FAILED(hr))
	{
		Logger::PrintLog(Logger::PrintType::Error, "Failed to create the D3D11 Device.");
		return false;
	}

	Logger::PrintLog(Logger::PrintType::Success, "D3D11 Device has been successfully created.");

	return true;
}
bool Engine::GraphicsDevice::CreateSwapChain(const HWND handle)
{
#pragma region "Swapchain Description"

	HRESULT hr;
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};

	//  Swap chain figures out the size of the window by checking window handle
	swapChainDesc.BufferDesc.Width = 0;
	swapChainDesc.BufferDesc.Height = 0;

	//  Color Format
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	//  Since we don't specify size, scaling is also unspecified.
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	//  Anti-aliasing
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	//  Pipeline is going to be rendering all of stuff.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;

	swapChainDesc.OutputWindow = handle;
	swapChainDesc.Windowed = true;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

#pragma endregion

#pragma region "Swapchain Creation Order"

	// Device Creation on DXGI
	ComPtr<IDXGIDevice> dxgiDevice;

	hr = m_Device.As(&dxgiDevice);

	if (FAILED(hr))
	{
		Logger::PrintLog(Logger::PrintType::Error, "Failed to get the DXGI Device.");
		return false;
	}

	// Adapter Creation on DXGI
	ComPtr<IDXGIAdapter> dxgiAdapter;

	hr = dxgiDevice.Get()->GetParent(IID_PPV_ARGS(dxgiAdapter.GetAddressOf()));

	if (FAILED(hr))
	{
		Logger::PrintLog(Logger::PrintType::Error, "Failed to get the DXGI Adapter.");
		return false;
	}

	// Method Implementation on DXGI
	ComPtr<IDXGIFactory> dxgiFactory;

	hr = dxgiAdapter.Get()->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf()));

	if (FAILED(hr))
	{
		Logger::PrintLog(Logger::PrintType::Error, "Failed to get the DXGI Factory.");
		return false;
	}

	// Swapchain creation on DXGI
	hr = dxgiFactory->CreateSwapChain(m_Device.Get(), &swapChainDesc, &m_Swapchain);

	if (FAILED(hr))
	{
		Logger::PrintLog(Logger::PrintType::Error, "Failed to create Swapchain.");
		return false;
	}

	Logger::PrintLog(Logger::PrintType::Success, "Swapchain has been successfully created.");

#pragma endregion

	return true;
}
bool Engine::GraphicsDevice::CreateRenderTargetView()
{
	ComPtr<ID3D11Texture2D> backBuffer;
	D3D11_RENDER_TARGET_VIEW_DESC targetViewDesc{};
	HRESULT hr;

	hr = m_Swapchain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
	if (FAILED(hr))
	{
		Logger::PrintLog(Logger::PrintType::Error, "Failed to get the Backbuffer.");
		return false;
	}

	hr = m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_RenderTargetView);
	if (FAILED(hr))
	{
		Logger::PrintLog(Logger::PrintType::Error, "Failed to create Render Target View.");
		return false;
	}

	m_Context->OMSetRenderTargets(1u, m_RenderTargetView.GetAddressOf(), nullptr);

	Logger::PrintLog(Logger::PrintType::Success, "Render Target View has been successfully created.");

	return true;
}
bool Engine::GraphicsDevice::CreateViewport(int width, int height)
{
	if (width < 640 && height < 480) 
	{
		Logger::PrintLog(Logger::PrintType::Error, "Use a windowsize bigger than 640x480");
		return false;
	}

	Viewport.Width = (float)width;
	Viewport.Height = (float)height;
	Viewport.MinDepth = 0;
	Viewport.MaxDepth = 1;
	Viewport.TopLeftX = 0;
	Viewport.TopLeftY = 0;

	m_Context->RSSetViewports(1u, &Viewport);
}
bool Engine::GraphicsDevice::UpdateFrame(float DeltaTime)
{
	ClearFrame();
	m_Swapchain->Present(1, 0);
	return true;
}
void Engine::GraphicsDevice::ClearFrame()
{
	// { 0.25f, 0.22f, 0.32f, 1.0f }
	const float clearColor[] = {0.084f, 0.106f, 0.122f, 1.0f};
	m_Context->ClearRenderTargetView(m_RenderTargetView.Get(), clearColor);
}
