#pragma once

#include <Core/CoreMinimal.h>
#include <Assets/ModelData.h>

class Model {

public:
	Model(ComPtr<ID3D11DeviceContext>& Context, ComPtr<ID3D11Device>& Device);

	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;
	~Model();

	void UpdateModel(float DeltaTime);
	uint16 GetIndicesCount();

protected:
	void InitializeModel(string imageName = "Sprite-0002.png");
	bool LoadSpriteImage(string imageName);

	ComPtr<ID3D11VertexShader> m_VertexShader;
	ComPtr<ID3D11PixelShader> m_PixelShader;

	ComPtr<ID3D11Buffer> m_VertexBuffer;
	ComPtr<ID3D11Buffer> m_IndexBuffer;

	ComPtr<ID3D11Texture2D> m_TextureBuffer;
	ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView;
	ComPtr<ID3D11SamplerState> m_SamplerState;

	std::vector<VertexData> vertices;
	std::vector<uint16> indices;

private:
	// Model icinde isler complex lesirse refactor
	// Hiyerarside dxdevices en yukarda.
	ComPtr<ID3D11DeviceContext>& dxContext;
	ComPtr<ID3D11Device>& dxDevice;
};