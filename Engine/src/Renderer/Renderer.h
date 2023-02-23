#pragma once

#include <Core/CoreMinimal.h>

#include <Renderer/RenderTypes.h>
#include <Assets/Model.h>

namespace Engine {

	class Renderer {

	public:
		Renderer(int width, int height);
		Renderer(const Renderer&) = delete;
		Renderer& operator= (const Renderer&) = delete;
		~Renderer();

		bool Initialize(const HWND handle);
		void UpdateFrame(float DeltaTime);

	protected:
		bool CreateDeviceContext(const DriverTypes typeValue = DriverTypes::Hardware, const FeatureTypesDX featureValue = FeatureTypesDX::Dx11);
		bool CreateSwapChain(const HWND handle);
		bool CreateRenderTargetView();
		bool CreatePixelShader(ComPtr<ID3DBlob>& Blob);
		bool CreateVertexShader(ComPtr<ID3DBlob>& Blob);
		bool CreateInputLayout(ComPtr<ID3DBlob>& Blob);
		bool CreateInputAssembler();
		void ClearFrame();

	private:
		ComPtr<ID3D11Device> m_Device;
		ComPtr<IDXGISwapChain> m_SwapChain;
		ComPtr<ID3D11DeviceContext> m_Context;

		ComPtr<ID3D11InputLayout> m_InputLayout;
		ComPtr<ID3D11RenderTargetView> m_RenderTargetView;

		ComPtr<ID3D11PixelShader> m_PixelShader;
		ComPtr<ID3D11VertexShader> m_VertexShader;

		D3D11_VIEWPORT Viewport;

		std::vector<Model*> Models;
	};
}

