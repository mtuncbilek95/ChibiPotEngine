#pragma once

#include <Core/CoreMinimal.h>

#define STB_IMAGE_IMPLEMENTATION
#include <ImageLoader/stb_image.h>

#include <Logger/Logger.h>

#include <Graphics/Device/GraphicsDevice.h>

namespace Engine {
	class TextureObject {
	public:
		TextureObject(GraphicsDevice* device) {
			m_GraphicsDevice = device;
		}

		bool InitializeTexture(string relativePath, XMINT2& imageOutputSize) {
			int imageChannels{}, imageDesiredChannels{ 4 };
			string filePath = Logger::GetInitialDir() + relativePath;
			const byte* ImageData = Engine::stbi_load(filePath.c_str(), imageOutputSize.x, imageOutputSize.y, &imageChannels, imageDesiredChannels);

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

			HRESULT hr = m_GraphicsDevice->m_Device->CreateTexture2D(&TextureBufferDesc, &TextureResourceData, &m_TextureBuffer);

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

			hr = m_GraphicsDevice->m_Device->CreateShaderResourceView(m_TextureBuffer.Get(), &ShaderDesc, &m_ShaderResourceView);

			if (FAILED(hr))
			{
				Logger::PrintLog(Logger::PrintType::Error, "Failed to create Shader Resource View.");
				return false;
			}

			Logger::PrintLog(Logger::PrintType::Success, "Shader Resource View has been created successfully.");

			return true;
		}

		bool LoadStates()
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

			hr = m_GraphicsDevice->m_Device->CreateSamplerState(&SamplerDesc, &m_SamplerState);

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

			hr = m_GraphicsDevice->m_Device->CreateBlendState(&blendDesc, &m_BlendState);

			if (FAILED(hr))
			{
				Logger::PrintLog(Logger::PrintType::Error, "Failed to create Blend State.");
				return false;
			}

			Logger::PrintLog(Logger::PrintType::Success, "Blend State has been created successfully.");

			return true;
		}

		void InitializeModel()
		{
			m_GraphicsDevice->m_Context->PSSetSamplers(0u, 1u, m_SamplerState.GetAddressOf());
			m_GraphicsDevice->m_Context->PSSetShaderResources(0u, 1u, m_ShaderResourceView.GetAddressOf());
			m_GraphicsDevice->m_Context->OMSetBlendState(m_BlendState.Get(), nullptr, D3D11_APPEND_ALIGNED_ELEMENT);
		}

	private:
		ComPtr<ID3D11Texture2D> m_TextureBuffer;
		ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView;

		ComPtr<ID3D11SamplerState> m_SamplerState;
		ComPtr<ID3D11BlendState> m_BlendState;

		std::vector<VertexData> vertices;
		std::vector<uint16> indices;

		GraphicsDevice* m_GraphicsDevice;
	};
}