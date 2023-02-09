#include "Model.h"

// Shader Resource View dipnot: its not data. its know how.


Model::Model(ComPtr<ID3D11DeviceContext>& Context, ComPtr<ID3D11Device>& Device) : dxContext(Context), dxDevice(Device)
{
	vertices.push_back({ {-0.5f, -0.5f, 1.0f}, {251, 183, 192, 255} });
	vertices.push_back({ {0.5f, -0.5f, 1.0f}, {251, 183, 192, 255} });
	vertices.push_back({ {-0.5f, 0.5f, 1.0f}, {251, 183, 192, 255} });
	vertices.push_back({ {0.5f, 0.5f, 1.0f}, {251, 183, 192, 255} });

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
	VertexResourceData.pSysMem = (void*)vertices.data();

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
	IndexResourceData.pSysMem = (void*)indices.data();

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

void Model::InitializeModel()
{
	const uint32 stride = sizeof(VertexData);
	const uint32 offset = 0u;

	dxContext->IASetVertexBuffers(0u, 1u, m_VertexBuffer.GetAddressOf(), &stride, &offset);
	dxContext->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	//     ContextPtr->VSSetConstantBuffers(0, 1u, ConstantBuffer.GetAddressOf());
}


void Model::LoadSpriteImage(string imageName)
{
	int imageWidth{}, imageHeight{}, imageChannels{}, imageDesiredChannels{ 4 };
	string filePath = Logger::GetInitialDir() + "/Game-Resource/King/" + imageName;
	byte* ImageData = stbi_load(filePath.c_str(), &imageWidth, &imageHeight, &imageChannels, imageDesiredChannels);

	int imagePitch = imageWidth * 4;	
}

void Model::UpdateModel(float DeltaTime)
{
}

uint16 Model::GetIndicesCount()
{
	return indices.size();
}
