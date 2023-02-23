#include "Renderer.h"
#include <Logger/Logger.h>
#include <Assets/ModelData.h>

Engine::Renderer::Renderer(const int width, const int height) : m_Device(nullptr), m_SwapChain(nullptr),
																m_Context(nullptr), m_RenderTargetView(nullptr)
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

bool Engine::Renderer::Initialize(const HWND handle)
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
	if (!CreateInputAssembler())
		return false;

	Model *king = new Model(m_Context, m_Device);

	Models.push_back(king);

	return true;
}

bool Engine::Renderer::CreateDeviceContext(const DriverTypes driverValue, const FeatureTypesDX featureValue)
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

bool Engine::Renderer::CreateSwapChain(const HWND handle)
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

#pragma region "Swapchain Order Creation"

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
	hr = dxgiFactory->CreateSwapChain(m_Device.Get(), &swapChainDesc, &m_SwapChain);

	if (FAILED(hr))
	{
		Logger::PrintLog(Logger::PrintType::Error, "Failed to create Swapchain.");
		return false;
	}

	Logger::PrintLog(Logger::PrintType::Success, "Swapchain has been successfully created.");

#pragma endregion

	return true;
}

bool Engine::Renderer::CreateRenderTargetView()
{
	ComPtr<ID3D11Texture2D> backBuffer;
	D3D11_RENDER_TARGET_VIEW_DESC targetViewDesc{};
	HRESULT hr;

	hr = m_SwapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
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

	Logger::PrintLog(Logger::PrintType::Success, "Render Target View has been successfully created.");
	return true;
}

bool Engine::Renderer::CreatePixelShader(ComPtr<ID3DBlob> &Blob)
{
	ComPtr<ID3DBlob> ErrorBlob;

	const string infoPixelShader = Logger::GetShaderData("PixelShader");

	D3DCompile(infoPixelShader.c_str(), infoPixelShader.length(), nullptr, nullptr, nullptr, "main", "ps_5_0",
			   D3DCOMPILE_ENABLE_STRICTNESS, 0, &Blob, &ErrorBlob);

	if (ErrorBlob.Get() != nullptr && ErrorBlob->GetBufferPointer() != nullptr)
		printf("%s", (char *)ErrorBlob->GetBufferPointer());

	HRESULT hr = m_Device->CreatePixelShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &m_PixelShader);

	if (FAILED(hr))
	{
		Logger::PrintLog(Logger::PrintType::Error, "Failed to create pixel shader.");
		return false;
	}

	m_Context->PSSetShader(m_PixelShader.Get(), nullptr, 0u);

	Logger::PrintLog(Logger::PrintType::Success, "Pixel Shader has been successfully created.");
	return true;
}

bool Engine::Renderer::CreateVertexShader(ComPtr<ID3DBlob> &Blob)
{
	ComPtr<ID3DBlob> ErrorBlob;

	const string infoVertexShader = Logger::GetShaderData("VertexShader");
	D3DCompile(infoVertexShader.c_str(), infoVertexShader.length(), nullptr, nullptr, nullptr, "main", "vs_5_0",
			   D3DCOMPILE_ENABLE_STRICTNESS, 0, &Blob, &ErrorBlob);

	if (ErrorBlob.Get() != nullptr && ErrorBlob->GetBufferPointer() != nullptr)
		printf("%s", (char *)ErrorBlob->GetBufferPointer());

	HRESULT hr = m_Device->CreateVertexShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &m_VertexShader);

	if (FAILED(hr))
	{
		Logger::PrintLog(Logger::PrintType::Error, "Failed to create vertex shader.");
		return false;
	}

	m_Context->VSSetShader(m_VertexShader.Get(), nullptr, 0u);

	Logger::PrintLog(Logger::PrintType::Success, "Vertex Shader has been successfully created.");

	return true;
}

bool Engine::Renderer::CreateInputLayout(ComPtr<ID3DBlob> &Blob)
{
	const D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

	HRESULT hr = m_Device->CreateInputLayout(inputElementDesc, (uint32)std::size(inputElementDesc),
											 Blob->GetBufferPointer(), Blob->GetBufferSize(), &m_InputLayout);

	if (FAILED(hr))
	{
		Logger::PrintLog(Logger::PrintType::Error, "Failed to create Input Layout");
		return false;
	}

	Logger::PrintLog(Logger::PrintType::Success, "Input Layout has been successfully created.");
	return true;
}

bool Engine::Renderer::CreateInputAssembler()
{
	m_Context->RSSetViewports(1u, &Viewport);
	m_Context->IASetInputLayout(m_InputLayout.Get());
	m_Context->OMSetRenderTargets(1u, m_RenderTargetView.GetAddressOf(), nullptr);
	m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return true;
}

void Engine::Renderer::UpdateFrame(float DeltaTime)
{
	ClearFrame();

	for (auto &model : Models)
	{
		model->UpdateModel(DeltaTime);
		m_Context->DrawIndexed(model->GetIndicesCount(), 0, 0);
	}

	m_SwapChain->Present(1, 0);
}

void Engine::Renderer::ClearFrame()
{
	//{ 0.25f, 0.22f, 0.32f, 1.0f }
	const float clearColor[] = {0.084f, 0.106f, 0.122f, 1.0f};
	m_Context->ClearRenderTargetView(m_RenderTargetView.Get(), clearColor);
}
