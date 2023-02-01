#include "Model.h"

Model::Model()
{
// #pragma region "Vertex Buffer"

//     D3D11_BUFFER_DESC VertexBufferDesc = {};
//     VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//     VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//     VertexBufferDesc.CPUAccessFlags = 0;
//     VertexBufferDesc.MiscFlags = 0;
//     VertexBufferDesc.ByteWidth = sizeof(vertices);
//     VertexBufferDesc.StructureByteStride = sizeof(Vertex);

//     D3D11_SUBRESOURCE_DATA VertexResourceData = {};
//     VertexResourceData.pSysMem = (void*)vertices;

//     DevicePtr->CreateBuffer(&VertexBufferDesc, &VertexResourceData, &VertexBuffer);

// #pragma endregion

// #pragma region "Index Buffer"

//     D3D11_BUFFER_DESC IndexBufferDesc = {};
//     IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
//     IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//     IndexBufferDesc.CPUAccessFlags = 0;
//     IndexBufferDesc.MiscFlags = 0;
//     IndexBufferDesc.ByteWidth = sizeof(indices);
//     IndexBufferDesc.StructureByteStride = sizeof(uint16);

//     D3D11_SUBRESOURCE_DATA IndexResourceData = {};
//     IndexResourceData.pSysMem = indices;

//     DevicePtr->CreateBuffer(&IndexBufferDesc, &IndexResourceData, &IndexBuffer);

// #pragma endregion

// #pragma region "Constant Buffer"

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
//     ContextPtr->VSSetConstantBuffers(0, 1u, ConstantBuffer.GetAddressOf());

// #pragma endregion
}

Model::~Model()
{
	m_VertexShader.Reset();
	m_PixelShader.Reset();

	m_VertexBuffer.Reset();
	m_IndexBuffer.Reset();
}
