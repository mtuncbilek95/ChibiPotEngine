#pragma once

#include <Core/CoreMinimal.h>

#include <Assets/ModelData.h>

class Model {
public:
	Model();

	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;
	~Model();

	VertexData m_MeshData;
	ComPtr<ID3D11VertexShader> m_VertexShader;
	ComPtr<ID3D11PixelShader> m_PixelShader;

	ComPtr<ID3D11Buffer> m_VertexBuffer;
	ComPtr<ID3D11Buffer> m_IndexBuffer;
};