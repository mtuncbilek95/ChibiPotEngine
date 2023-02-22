#pragma once

#include <Core/CoreMinimal.h>

enum class ShaderType : uint8
{
	VertexShader,
	DomainShader,
	GeometryShader,
	PixelShader
};

class Shader
{
public:
	/**
	 * @brief Construct a new Shader object
	 *
	 * @param context	Get the address of initialized D3D11DeviceContext.
	 * @param device	Get the address of initialized D3D11Device.
	 */
	Shader(ComPtr<ID3D11DeviceContext> &context, ComPtr<ID3D11Device> &device);
	/**
	 * @brief Compiles the shader with ID3DBlob which stores the data for vertex and material.
	 *
	 * @param shaderName 	Name of the shader which will be initialized. Example: "ObjectFolder/ObjectVertexShader"
	 * @param type			Choose the type of the shader.
	 *
	 * @return if returns false, related object wont be spawned.
	 */
	bool CompileShader(string shaderName, ShaderType type);
};