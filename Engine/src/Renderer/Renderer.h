#ifndef RENDERER_H
#define RENDERER_H

#include "DriverTypes.h"
#include <d3d11.h>
#include <wrl.h>

using namespace Microsoft::WRL;

namespace Engine {

	class Renderer {

	public:
		Renderer();
		Renderer(const Renderer&) = delete;
		Renderer& operator= (const Renderer&) = delete;
		~Renderer();

		bool Initialize(HWND handle);
		bool CreateDeviceContext(DriverTypes typeValue = DriverTypes::Hardware);
		bool CreateSwapChain(HWND handle);
		bool CreateRenderTargetView();
		bool CreatePixelShader(ComPtr<ID3DBlob>& Blob);
		bool CreateVertexShader(ComPtr<ID3DBlob>& Blob);
		bool CreateInputLayout(ComPtr<ID3DBlob>& Blob);

		void UpdateFrame();
		void ClearFrame();

	private:

		ComPtr<ID3D11Device> m_Device;
		ComPtr<IDXGISwapChain> m_SwapChain;
		ComPtr<ID3D11DeviceContext> m_Context;

		ComPtr<ID3D11InputLayout> m_InputLayout;
		ComPtr<ID3D11RenderTargetView> m_RenderTargetView;

	};
}

#endif // RENDERER_H