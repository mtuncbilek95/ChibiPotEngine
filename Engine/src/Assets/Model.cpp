#include "Model.h"
#include <Logger/Logger.h>

#define STB_IMAGE_IMPLEMENTATION
#include <ImageLoader/stb_image.h>

// Shader Resource View dipnot: its not data. its know how.

Model::Model(ComPtr<ID3D11DeviceContext> &Context, ComPtr<ID3D11Device> &Device) : dxContext(Context), dxDevice(Device)
{
	/////////////// Square Initialization ///////////////

	vertices.push_back({{-0.5f, -0.5f, 1.0f}, {251, 183, 192, 255}});
	vertices.push_back({{0.5f, -0.5f, 1.0f}, {251, 183, 192, 255}});
	vertices.push_back({{-0.5f, 0.5f, 1.0f}, {251, 183, 192, 255}});
	vertices.push_back({{0.5f, 0.5f, 1.0f}, {251, 183, 192, 255}});

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(1);

	/////////////// Vertex Buffer ///////////////

	D3D11_BUFFER_DESC VertexBufferDesc = {};
	VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	VertexBufferDesc.CPUAccessFlags = 0;
	VertexBufferDesc.MiscFlags = 0;
	VertexBufferDesc.ByteWidth = sizeof(VertexData) * vertices.size(); // Need to fix this implementation
	VertexBufferDesc.StructureByteStride = sizeof(VertexData);

	D3D11_SUBRESOURCE_DATA VertexResourceData = {};
	VertexResourceData.pSysMem = (void *)vertices.data();

	dxDevice->CreateBuffer(&VertexBufferDesc, &VertexResourceData, &m_VertexBuffer);

	/////////////// Index Buffer ///////////////

	D3D11_BUFFER_DESC IndexBufferDesc = {};
	IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	IndexBufferDesc.CPUAccessFlags = 0;
	IndexBufferDesc.MiscFlags = 0;
	IndexBufferDesc.ByteWidth = sizeof(uint16) * indices.size(); // Need to fix this implementation

	IndexBufferDesc.StructureByteStride = sizeof(uint16);

	D3D11_SUBRESOURCE_DATA IndexResourceData = {};
	IndexResourceData.pSysMem = (void *)indices.data();

	dxDevice->CreateBuffer(&IndexBufferDesc, &IndexResourceData, &m_IndexBuffer);

	/////////////// Constant Buffer ///////////////

	//     D3D11_BUFFER_DESC ConstantBufferDesc = {};
	//     ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//     ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	//     ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//     ConstantBufferDesc.MiscFlags = 0;
	//     ConstantBufferDesc.ByteWidth = sizeof(cbMatrix);
	//     ConstantBufferDesc.StructureByteStride = 0;

	//     D3D11_SUBRESOURCE_DATA ConstantResourceData = {};
	//     ConstantResourceData.pSysMem = &cbMatrix;

	//     DevicePtr->CreateBuffer(&ConstantBufferDesc, &ConstantResourceData, &ConstantBuffer);
}

Model::~Model()
{
	m_VertexShader.Reset();
	m_PixelShader.Reset();

	m_VertexBuffer.Reset();
	m_IndexBuffer.Reset();
}

void Model::InitializeModel(string imageName)
{
	LoadSpriteImage(imageName);

	const uint32 stride = sizeof(VertexData);
	const uint32 offset = 0u;

	dxContext->IASetVertexBuffers(0u, 1u, m_VertexBuffer.GetAddressOf(), &stride, &offset);
	dxContext->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	dxContext->PSSetShaderResources(0u, 1u, m_ShaderResourceView.GetAddressOf());
	dxContext->PSGetSamplers(0u, 1u, m_SamplerState.GetAddressOf());
	//     ContextPtr->VSSetConstantBuffers(0, 1u, ConstantBuffer.GetAddressOf());
}

bool Model::LoadSpriteImage(string imageName)
{
	int imageWidth{}, imageHeight{}, imageChannels{}, imageDesiredChannels{4};
	string filePath = Logger::GetInitialDir() + "/Game-Resource/King/" + imageName;
	byte *ImageData = stbi_load(filePath.c_str(), &imageWidth, &imageHeight, &imageChannels, imageDesiredChannels);

	int imagePitch = imageWidth * 4;

	D3D11_TEXTURE2D_DESC TextureBufferDesc{};
	TextureBufferDesc.Width = imageWidth;
	TextureBufferDesc.Height = imageHeight;
	TextureBufferDesc.MipLevels = 1;
	TextureBufferDesc.ArraySize = 1;
	TextureBufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	TextureBufferDesc.SampleDesc.Count = 1;
	TextureBufferDesc.SampleDesc.Quality = 0;
	TextureBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	TextureBufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA TextureResourceData{};
	TextureResourceData.pSysMem = (void *)ImageData;
	TextureResourceData.SysMemPitch = imagePitch;

	HRESULT hr = dxDevice->CreateTexture2D(&TextureBufferDesc, &TextureResourceData, &m_TextureBuffer);

	if (FAILED(hr))
	{
		CONSOLE_LOG(CB_Error, "Failed to create Texture.");
		return false;
	}

	CONSOLE_LOG(CB_Success, "Texture has been created successfully.");

	hr = dxDevice->CreateShaderResourceView(m_TextureBuffer.Get(), nullptr, &m_ShaderResourceView);

	if (FAILED(hr))
	{
		CONSOLE_LOG(CB_Error, "Failed to create Shader Resource View.");
		return false;
	}

	CONSOLE_LOG(CB_Success, "Shader Resource View has been created successfully.");

	D3D11_SAMPLER_DESC SamplerDesc{};
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamplerDesc.MipLODBias = 1.0f;
	SamplerDesc.MaxAnisotropy = 1;
	SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	for (auto &el : SamplerDesc.BorderColor)
	{
		el = 1.0f;
	}
	SamplerDesc.MinLOD = -FLT_MAX;
	SamplerDesc.MaxLOD = FLT_MAX;

	hr = dxDevice->CreateSamplerState(&SamplerDesc, &m_SamplerState);

	if (FAILED(hr))
	{
		CONSOLE_LOG(CB_Error, "Failed to create Sampler State.");
		return false;
	}

	CONSOLE_LOG(CB_Success, "Sampler State has been created successfully.");

	return true;
}

void Model::UpdateModel(float DeltaTime)
{
}

uint16 Model::GetIndicesCount()
{
	return indices.size();
}
