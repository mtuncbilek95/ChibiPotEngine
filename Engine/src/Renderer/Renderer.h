#pragma once

#include "DriverTypes.h"
#include <d3d11.h>
#include <wrl.h>

using namespace Microsoft::WRL;

namespace Engine {

	class Renderer {

	public:
		Renderer(int width, int height);
		Renderer(const Renderer&) = delete;
		Renderer& operator= (const Renderer&) = delete;
		~Renderer();

		bool Initialize(HWND handle);
		void UpdateFrame();

	protected:
		bool CreateDeviceContext(DriverTypes typeValue = DriverTypes::Hardware);
		bool CreateSwapChain(HWND handle);
		bool CreateRenderTargetView();
		bool CreatePixelShader(ComPtr<ID3DBlob>& Blob);
		bool CreateVertexShader(ComPtr<ID3DBlob>& Blob);
		bool CreateInputLayout(ComPtr<ID3DBlob>& Blob);
		void ClearFrame();

	private:
		ComPtr<ID3D11Device> m_Device;
		ComPtr<IDXGISwapChain> m_SwapChain;
		ComPtr<ID3D11DeviceContext> m_Context;

		ComPtr<ID3D11InputLayout> m_InputLayout;
		ComPtr<ID3D11RenderTargetView> m_RenderTargetView;

		D3D11_VIEWPORT Viewport;
	};
}