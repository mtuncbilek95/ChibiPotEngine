#pragma once

#include <Core/CoreMinimal.h>
#include <Assets/ModelData.h>

class Texture2D
{
public:
    Texture2D(ComPtr<ID3D11Buffer>& m_VertexBuffer, ComPtr<ID3D11Device>& dxDevice)
    {
        vertices.push_back({{-0.5f, -0.5f, 1.0f}, {0, 1}});
        vertices.push_back({{0.5f, -0.5f, 1.0f}, {0.1f, 1}});
        vertices.push_back({{-0.5f, 0.5f, 1.0f}, {0, 0}});
        vertices.push_back({{0.5f, 0.5f, 1.0f}, {0.1f, 0}});

        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(1);
        indices.push_back(2);
        indices.push_back(3);
        indices.push_back(1);

        D3D11_BUFFER_DESC VertexBufferDesc = {};
        VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        VertexBufferDesc.CPUAccessFlags = 0;
        VertexBufferDesc.MiscFlags = 0;
        VertexBufferDesc.ByteWidth = sizeof(VertexData) * vertices.size();
        VertexBufferDesc.StructureByteStride = sizeof(VertexData);

        D3D11_SUBRESOURCE_DATA VertexResourceData = {};
        VertexResourceData.pSysMem = (void *)vertices.data();

        dxDevice->CreateBuffer(&VertexBufferDesc, &VertexResourceData, &m_VertexBuffer);
    }

private:
    std::vector<VertexData> vertices;
    std::vector<byte> indices;
};