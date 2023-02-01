#include "Renderer.h"

#include <Assets/ModelData.h>

//	Beyzanin sevdigi renk #FBB7C0 

const VertexData vertices[] =
{
	{{-0.5f, -0.5f, 1.0f}, {0, 255, 0, 0}},
	{{-0.5f, 0.5f, 1.0f}, {0, 255, 0, 0}},
	{{0.5f, -0.5f, 1.0f}, {0, 255, 0, 0}},
	{{0.5f, 0.5f, 1.0f}, {0, 255, 0, 0}},
};

const uint16 indices[] = {
	0, 1, 2,
	1, 3, 2,
};

Engine::Renderer::Renderer(const int width, const int height) : m_Device(nullptr), m_SwapChain(nullptr), m_Context(nullptr), m_RenderTargetView(nullptr)
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

	CreateInputAssembler();
	TriangleTest();

	return true;
}

bool Engine::Renderer::CreateDeviceContext(const DriverTypes typeValue)
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
		CONSOLE_LOG(CB_Warning, "Failed to create the D3D11 Device.");
		return false;
	}
	CONSOLE_LOG(CB_Success, "D3D11 Device has been successfully created.");

	return true;
}

bool Engine::Renderer::CreateSwapChain(const HWND handle)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};

	//  Swap chain figures out the size of the window by checking window handle
	swapChainDesc.BufferDesc.Width = (uint32)Viewport.Width;
	swapChainDesc.BufferDesc.Height = (uint32)Viewport.Height;

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

	ComPtr<IDXGIDevice> dxgiDevice;

	HRESULT hr = m_Device.As(&dxgiDevice);
	if (FAILED(hr))
	{
		CONSOLE_LOG(CB_Error, "Failed to get the DXGI Device.");
		return false;
	}

	ComPtr<IDXGIAdapter> dxgiAdapter;

	hr = dxgiDevice.Get()->GetParent(IID_PPV_ARGS(dxgiAdapter.GetAddressOf()));

	if (FAILED(hr))
	{
		CONSOLE_LOG(CB_Error, "Failed to get the DXGI Adapter.");
		return false;
	}

	ComPtr<IDXGIFactory> dxgiFactory;

	hr = dxgiAdapter.Get()->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf()));

	if (FAILED(hr))
	{
		CONSOLE_LOG(CB_Error, "Failed to get the DXGI Factory.");
		return false;
	}

	hr = dxgiFactory->CreateSwapChain(m_Device.Get(), &swapChainDesc, &m_SwapChain);

	if (FAILED(hr))
	{
		CONSOLE_LOG(CB_Error, "Failed to create Swapchain.");
		return false;
	}

	CONSOLE_LOG(CB_Success, "Swapchain has been successfully created.");

	return true;
}

bool Engine::Renderer::CreateRenderTargetView()
{
	ComPtr<ID3D11Texture2D> backBuffer;

	D3D11_RENDER_TARGET_VIEW_DESC targetViewDesc{};

	HRESULT hr = m_SwapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
	if (FAILED(hr))
	{
		CONSOLE_LOG(CB_Error, "Failed to get the Backbuffer.");
		return false;
	}

	hr = m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_RenderTargetView);
	if (FAILED(hr))
	{
		CONSOLE_LOG(CB_Error, "Failed to create Render Target View.");
		return false;
	}

	CONSOLE_LOG(CB_Success, "Render Target View has been successfully created.");
	return true;
}

bool Engine::Renderer::CreatePixelShader(ComPtr<ID3DBlob>& Blob)
{
	ComPtr<ID3DBlob> ErrorBlob;

	const string infoPixelShader = Logger::GetShaderData("PixelShader");

	D3DCompile(infoPixelShader.c_str(), infoPixelShader.length(), nullptr, nullptr, nullptr, "main", "ps_5_0",
		D3DCOMPILE_ENABLE_STRICTNESS, 0, &Blob, &ErrorBlob);

	if (ErrorBlob.Get() != nullptr && ErrorBlob->GetBufferPointer() != nullptr)
		printf("%s", (char*)ErrorBlob->GetBufferPointer());

	HRESULT hr = m_Device->CreatePixelShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &m_PixelShader);

	if (FAILED(hr))
	{
		CONSOLE_LOG(CB_Error, "Failed to create pixel shader.");
		return false;
	}

	m_Context->PSSetShader(m_PixelShader.Get(), nullptr, 0u);

	CONSOLE_LOG(CB_Success, "Pixel Shader has been successfully created.");
	return true;
}

bool Engine::Renderer::CreateVertexShader(ComPtr<ID3DBlob>& Blob)
{
	ComPtr<ID3DBlob> ErrorBlob;

	const string infoVertexShader = Logger::GetShaderData("VertexShader");
	D3DCompile(infoVertexShader.c_str(), infoVertexShader.length(), nullptr, nullptr, nullptr, "main", "vs_5_0",
		D3DCOMPILE_ENABLE_STRICTNESS, 0, &Blob, &ErrorBlob);

	if (ErrorBlob.Get() != nullptr && ErrorBlob->GetBufferPointer() != nullptr)
		printf("%s", (char*)ErrorBlob->GetBufferPointer());

	HRESULT hr = m_Device->CreateVertexShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &m_VertexShader);

	if (FAILED(hr))
	{
		CONSOLE_LOG(CB_Error, "Failed to create vertex shader.");
		return false;
	}

	m_Context->VSSetShader(m_VertexShader.Get(), nullptr, 0u);

	CONSOLE_LOG(CB_Success, "Vertex Shader has been successfully created.");

	return true;
}

bool Engine::Renderer::CreateInputLayout(ComPtr<ID3DBlob>& Blob)
{
	const D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"Color", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12u, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	HRESULT hr = m_Device->CreateInputLayout(inputElementDesc, static_cast<uint32>(_countof(inputElementDesc)),
		Blob->GetBufferPointer(), Blob->GetBufferSize(), &m_InputLayout);

	if (FAILED(hr))
	{
		CONSOLE_LOG(CB_Error, "Failed to create Input Layout");
		return false;
	}

	CONSOLE_LOG(CB_Success, "Input Layout has been successfully created.");
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
	m_Context->DrawIndexed(_countof(indices), 0u, 0u);
	m_SwapChain->Present(1, 0);
}

void Engine::Renderer::ClearFrame()
{
	const float clearColor[] = { 0.084f, 0.106f, 0.122f, 1.0f };
	m_Context->ClearRenderTargetView(m_RenderTargetView.Get(), clearColor);
}

void Engine::Renderer::TriangleTest()
{
	D3D11_BUFFER_DESC VertexBufferDesc = {};
	VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	VertexBufferDesc.CPUAccessFlags = 0;
	VertexBufferDesc.MiscFlags = 0;
	VertexBufferDesc.ByteWidth = sizeof(vertices);
	VertexBufferDesc.StructureByteStride = sizeof(VertexData);

	D3D11_SUBRESOURCE_DATA VertexResourceData = {};
	VertexResourceData.pSysMem = vertices;

	m_Device->CreateBuffer(&VertexBufferDesc, &VertexResourceData, &vertexBuffer);

	D3D11_BUFFER_DESC IndexBufferDesc = {};
	IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	IndexBufferDesc.CPUAccessFlags = 0;
	IndexBufferDesc.MiscFlags = 0;
	IndexBufferDesc.ByteWidth = sizeof(indices);
	IndexBufferDesc.StructureByteStride = sizeof(uint16);

	D3D11_SUBRESOURCE_DATA IndexResourceData = {};
	IndexResourceData.pSysMem = indices;

	m_Device->CreateBuffer(&IndexBufferDesc, &IndexResourceData, &indexBuffer);

	const uint32 stride = sizeof(VertexData);
	const uint32 offset = 0u;

	m_Context->IASetVertexBuffers(0u, 1u, vertexBuffer.GetAddressOf(), &stride, &offset);
	m_Context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

}
