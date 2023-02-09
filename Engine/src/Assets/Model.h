#pragma once

#include <Core/CoreMinimal.h>
#include <Assets/ModelData.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


class Model {

public:
	Model(ComPtr<ID3D11DeviceContext>& Context, ComPtr<ID3D11Device>& Device);

	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;
	~Model();

	void UpdateModel(float DeltaTime);
	uint16 GetIndicesCount();

protected:
	void InitializeModel();
	// Idle-0001.png
	void LoadSpriteImage(string imageName = "Idle-0001.png");

	ComPtr<ID3D11VertexShader> m_VertexShader;
	ComPtr<ID3D11PixelShader> m_PixelShader;

	ComPtr<ID3D11Buffer> m_VertexBuffer;
	ComPtr<ID3D11Buffer> m_IndexBuffer;

	std::vector<VertexData> vertices;
	std::vector<uint16> indices;

private:
	// Model icinde isler complex lesirse refactor
	// Hiyerarside dxdevices en yukarda.
	ComPtr<ID3D11DeviceContext>& dxContext;
	ComPtr<ID3D11Device>& dxDevice;
};