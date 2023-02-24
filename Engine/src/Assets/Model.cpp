#include "Model.h"
#include <Logger/Logger.h>

#define STB_IMAGE_IMPLEMENTATION
#include <ImageLoader/stb_image.h>

// Shader Resource View dipnot: its not data. its know how.

Model::Model(ComPtr<ID3D11DeviceContext>& Context, ComPtr<ID3D11Device>& Device) : dxContext(Context), dxDevice(Device)
{
	/////////////// Square Initialization ///////////////

	vertices.push_back({ {-0.5f, -0.5f, 1.0f}, {0,1} });
	vertices.push_back({ {0.5f, -0.5f, 1.0f}, {0.1f,1} });
	vertices.push_back({ {-0.5f, 0.5f, 1.0f}, {0,0} });
	vertices.push_back({ {0.5f, 0.5f, 1.0f}, {0.1f,0} });

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(1);

	constantBuffer.tilex = 0.1f;

	/////////////// Vertex Buffer ///////////////

	D3D11_BUFFER_DESC VertexBufferDesc = {};
	VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	VertexBufferDesc.CPUAccessFlags = 0;
	VertexBufferDesc.MiscFlags = 0;
	VertexBufferDesc.ByteWidth = sizeof(VertexData) * vertices.size();
	VertexBufferDesc.StructureByteStride = sizeof(VertexData);

	D3D11_SUBRESOURCE_DATA VertexResourceData = {};
	VertexResourceData.pSysMem = (void*)vertices.data();

	dxDevice->CreateBuffer(&VertexBufferDesc, &VertexResourceData, &m_VertexBuffer);

	/////////////// Index Buffer ///////////////

	D3D11_BUFFER_DESC IndexBufferDesc = {};
	IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	IndexBufferDesc.CPUAccessFlags = 0;
	IndexBufferDesc.MiscFlags = 0;
	IndexBufferDesc.ByteWidth = sizeof(uint16) * indices.size();

	IndexBufferDesc.StructureByteStride = sizeof(uint16);

	D3D11_SUBRESOURCE_DATA IndexResourceData = {};
	IndexResourceData.pSysMem = (void*)indices.data();

	dxDevice->CreateBuffer(&IndexBufferDesc, &IndexResourceData, &m_IndexBuffer);

	/////////////// Constant Buffer ///////////////

	D3D11_BUFFER_DESC ConstantBufferDesc = {};
	ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ConstantBufferDesc.MiscFlags = 0;
	ConstantBufferDesc.ByteWidth = 16u;
	ConstantBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA ConstantResourceData = {};
	ConstantResourceData.pSysMem = &constantBuffer;

	dxDevice->CreateBuffer(&ConstantBufferDesc, &ConstantResourceData, &m_ConstantBuffer);

	InitializeModel();
}

Model::~Model()
{
	m_VertexBuffer.Reset();
	m_IndexBuffer.Reset();
}

void Model:: InitializeModel(string imageName)
{
	LoadStates();
	LoadSpriteImage(imageName);
	const uint32 stride = sizeof(VertexData);
	const uint32 offset = 0u;

	dxContext->IASetVertexBuffers(0u, 1u, m_VertexBuffer.GetAddressOf(), &stride, &offset);
	dxContext->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	dxContext->VSSetConstantBuffers(0, 1u, m_ConstantBuffer.GetAddressOf());
	dxContext->PSSetSamplers(0u, 1u, m_SamplerState.GetAddressOf());
	dxContext->PSSetShaderResources(0u, 1u, m_ShaderResourceView.GetAddressOf());
	dxContext->OMSetBlendState(m_BlendState.Get(), nullptr, D3D11_APPEND_ALIGNED_ELEMENT);
}

bool Model::LoadSpriteImage(string imageName)
{
	int imageWidth{}, imageHeight{}, imageChannels{}, imageDesiredChannels{ 4 };
	string filePath = Logger::GetInitialDir() + "/Game-Resource/King/" + imageName;
	const byte* ImageData = Engine::stbi_load(filePath.c_str(), &imageWidth, &imageHeight, &imageChannels, imageDesiredChannels);

	int imagePitch = imageWidth * 4 * sizeof(byte);

	D3D11_TEXTURE2D_DESC TextureBufferDesc{};
	TextureBufferDesc.Width = imageWidth;
	TextureBufferDesc.Height = imageHeight;
	TextureBufferDesc.MipLevels = 1;
	TextureBufferDesc.ArraySize = 1;
	TextureBufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	TextureBufferDesc.SampleDesc.Count = 1;
	TextureBufferDesc.SampleDesc.Quality = 0;
	TextureBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	TextureBufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA TextureResourceData{};
	TextureResourceData.pSysMem = ImageData;
	TextureResourceData.SysMemPitch = imagePitch;

	HRESULT hr = dxDevice->CreateTexture2D(&TextureBufferDesc, &TextureResourceData, &m_TextureBuffer);

	if (FAILED(hr)) {
		Logger::PrintLog(Logger::PrintType::Error, "Failed to create Texture.");
		return false;
	}

	Logger::PrintLog(Logger::PrintType::Success, "Texture has been created successfully.");

	D3D11_SHADER_RESOURCE_VIEW_DESC ShaderDesc{};
	ShaderDesc.Format = TextureBufferDesc.Format;
	ShaderDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	ShaderDesc.Texture2D.MostDetailedMip = 0;
	ShaderDesc.Texture2D.MipLevels = -1;

	hr = dxDevice->CreateShaderResourceView(m_TextureBuffer.Get(), &ShaderDesc, &m_ShaderResourceView);

	if (FAILED(hr))
	{
		Logger::PrintLog(Logger::PrintType::Error, "Failed to create Shader Resource View.");
		return false;
	}

	Logger::PrintLog(Logger::PrintType::Success, "Shader Resource View has been created successfully.");

	return true;
}

bool Model::LoadStates()
{
	HRESULT hr;

	D3D11_SAMPLER_DESC SamplerDesc{};
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.MipLODBias = 1.0f;
	SamplerDesc.MaxAnisotropy = 1;
	SamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;

	for (auto& el : SamplerDesc.BorderColor)
	{
		el = 0.0f;
	}

	SamplerDesc.MinLOD = 0;
	SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = dxDevice->CreateSamplerState(&SamplerDesc, &m_SamplerState);

	if (FAILED(hr))
	{
		Logger::PrintLog(Logger::PrintType::Error, "Failed to create Sampler State.");
		return false;
	}

	Logger::PrintLog(Logger::PrintType::Success, "Sampler State has been created successfully.");

	D3D11_BLEND_DESC blendDesc{};
	D3D11_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};

	renderTargetBlendDesc.BlendEnable = true;
	renderTargetBlendDesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
	renderTargetBlendDesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	renderTargetBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;
	renderTargetBlendDesc.SrcBlendAlpha = D3D11_BLEND_ONE;
	renderTargetBlendDesc.DestBlendAlpha = D3D11_BLEND_ZERO;
	renderTargetBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
	renderTargetBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	blendDesc.RenderTarget[0] = renderTargetBlendDesc;
	blendDesc.IndependentBlendEnable = true;
	blendDesc.AlphaToCoverageEnable = false;

	hr = dxDevice->CreateBlendState(&blendDesc, &m_BlendState);

	if (FAILED(hr))
	{
		Logger::PrintLog(Logger::PrintType::Error, "Failed to create Blend State.");
		return false;
	}

	Logger::PrintLog(Logger::PrintType::Success, "Blend State has been created successfully.");

	return true;
}

void Model::UpdateModel(float DeltaTime)
{
	static float counter;
	counter += DeltaTime;

	if (counter >= 0.1f) {
		constantBuffer.tilex > 0.9f ? constantBuffer.tilex = 0.1f : constantBuffer.tilex += 0.1f;

		D3D11_MAPPED_SUBRESOURCE cbSubresource{};
		dxContext->Map(m_ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &cbSubresource);
		memcpy(cbSubresource.pData, &constantBuffer, 16u);
		dxContext->Unmap(m_ConstantBuffer.Get(), 0);
 
		counter = 0;
	}

}

uint16 Model::GetIndicesCount()
{
	return indices.size();
}
