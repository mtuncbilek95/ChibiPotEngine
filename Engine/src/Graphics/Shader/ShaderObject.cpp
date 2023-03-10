#include "ShaderObject.h"

#include <Logger/Logger.h>
#include <Graphics/Device/GraphicsDevice.h>

Engine::ShaderObject::ShaderObject(Engine::GraphicsDevice* _graphicsDevice)
{
	this->graphicsDevice = _graphicsDevice;
}

bool Engine::ShaderObject::CompileShader(ComPtr<ID3DBlob>& Blob, string shaderName, ShaderType type)
{
	Logger::PrintLog(Logger::PrintType::Warning, "CompileShader() has no implemented method yet!");
	return false;
}

bool Engine::ShaderObject::CompileVertexShader()
{
	ComPtr<ID3DBlob> ErrorBlob;

	const string infoVertexShader = Logger::GetShaderData("VertexShader");
	D3DCompile(infoVertexShader.c_str(), infoVertexShader.length(), nullptr, nullptr, nullptr, "main", "vs_5_0",
		D3DCOMPILE_ENABLE_STRICTNESS, 0, &m_Blob, &ErrorBlob);

	if (ErrorBlob.Get() != nullptr && ErrorBlob->GetBufferPointer() != nullptr)
		printf("%s", (char*)ErrorBlob->GetBufferPointer());

	HRESULT hr = graphicsDevice->m_Device->CreateVertexShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_VertexShader);

	if (FAILED(hr))
	{
		Logger::PrintLog(Logger::PrintType::Error, "Failed to create vertex shader.");
		return false;
	}

	graphicsDevice->m_Context->VSSetShader(m_VertexShader.Get(), nullptr, 0u);

	Logger::PrintLog(Logger::PrintType::Success, "Vertex Shader has been successfully created.");

	return true;
}

bool Engine::ShaderObject::CompilePixelShader()
{
	ComPtr<ID3DBlob> ErrorBlob;

	const string infoPixelShader = Logger::GetShaderData("PixelShader");

	D3DCompile(infoPixelShader.c_str(), infoPixelShader.length(), nullptr, nullptr, nullptr, "main", "ps_5_0",
		D3DCOMPILE_ENABLE_STRICTNESS, 0, &m_Blob, &ErrorBlob);

	if (ErrorBlob.Get() != nullptr && ErrorBlob->GetBufferPointer() != nullptr)
		printf("%s", (char*)ErrorBlob->GetBufferPointer());

	HRESULT hr = graphicsDevice->m_Device->CreatePixelShader(m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), nullptr, &m_PixelShader);

	if (FAILED(hr))
	{
		Logger::PrintLog(Logger::PrintType::Error, "Failed to create pixel shader.");
		return false;
	}

	graphicsDevice->m_Context->PSSetShader(m_PixelShader.Get(), nullptr, 0u);

	Logger::PrintLog(Logger::PrintType::Success, "Pixel Shader has been successfully created.");
	return true;
}

bool Engine::ShaderObject::CreateInputLayout()
{
	const D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	HRESULT hr = graphicsDevice->m_Device->CreateInputLayout(inputElementDesc, (uint32)std::size(inputElementDesc),
		m_Blob->GetBufferPointer(), m_Blob->GetBufferSize(), &m_InputLayout);

	if (FAILED(hr))
	{
		Logger::PrintLog(Logger::PrintType::Error, "Failed to create Input Layout");
		return false;
	}

	graphicsDevice->m_Context->IASetInputLayout(m_InputLayout.Get());

	Logger::PrintLog(Logger::PrintType::Success, "Input Layout has been successfully created.");
	return true;
}


