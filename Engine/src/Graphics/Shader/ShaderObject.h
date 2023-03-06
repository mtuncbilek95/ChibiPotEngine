#pragma once

#include <Core/CoreMinimal.h>


enum class ShaderType : uint8
{
	VertexShader,
	DomainShader,
	GeometryShader,
	PixelShader
};

namespace Engine
{
	class GraphicsDevice;

	class ShaderObject
	{
	public:
		/**
		 * @brief Construct a new Shader Device object
		 * @param _graphicsDevice
		*/
		ShaderObject(GraphicsDevice* _graphicsDevice);
		/**
		 * @brief Compiles the shader with ID3DBlob which stores the data for vertex and material.
		 * @param shaderName 	Name of the shader which will be initialized. Example: "ObjectFolder/ObjectVertexShader"
		 * @param type			Choose the type of the shader.
		 * @return if returns false, related object wont be spawned.
		*/
		bool CompileShader(ComPtr<ID3DBlob>& Blob, string shaderName, ShaderType type);

		/**
		 * @brief Compiles the shader with ID3DBlob which stores the data for vertex and material.
		 * @param Blob Data Container.
		 * @return if returns false, related object wont be spawned.
		*/
		bool CompileVertexShader(ComPtr<ID3DBlob>& Blob);
		/**
		 * @brief Compiles the shader with ID3DBlob which stores the data for vertex and material.
		 * @param Blob Data Container.
		 * @return if returns false, related object wont be spawned.
		*/
		bool CompilePixelShader(ComPtr<ID3DBlob>& Blob);

		/**
		 * @brief Binds Shader system with DirectX via m_InputLayout in GraphicsDevice.
		 * @param Blob Data Container.
		 * @return if returns false, related object wont be spawned.
		*/
		bool CreateInputLayout(ComPtr<ID3DBlob>& Blob);

	private:
		GraphicsDevice* graphicsDevice;

		ComPtr<ID3D11VertexShader> m_VertexShader;
		ComPtr<ID3D11PixelShader> m_PixelShader;
	};
}