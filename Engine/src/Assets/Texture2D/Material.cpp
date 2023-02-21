#include "Material.h"

#include <Logger/Logger.h>

bool Material::CreatePixelShader(ComPtr<ID3D11Device> &p_device, ComPtr<ID3DBlob> &p_Blob)
{
	ComPtr<ID3DBlob> ErrorBlob;

	const string infoPixelShader = Logger::GetShaderData("PixelShader");

	D3DCompile(infoPixelShader.c_str(), infoPixelShader.length(), nullptr, nullptr, nullptr, "main", "ps_5_0",
			   D3DCOMPILE_ENABLE_STRICTNESS, 0, &p_Blob, &ErrorBlob);

	if (ErrorBlob.Get() != nullptr && ErrorBlob->GetBufferPointer() != nullptr)
		Logger::PrintLog(Logger::PrintType::Error, (char *)ErrorBlob->GetBufferPointer());

	HRESULT hr = p_device->CreatePixelShader(p_Blob->GetBufferPointer(), p_Blob->GetBufferSize(), nullptr, &m_PixelShader);

	if (FAILED(hr))
	{
		Logger::PrintLog(Logger::PrintType::Error, "Failed to create pixel shader.");
		return false;
	}

	Logger::PrintLog(Logger::PrintType::Success, "Pixel Shader has been successfully created.");

	return true;
}
