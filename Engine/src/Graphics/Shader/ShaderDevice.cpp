#include "ShaderDevice.h"

#include <Logger/Logger.h>


Engine::ShaderDevice::ShaderDevice(Engine::GraphicsDevice* _graphicsDevice)
{
	this->graphicsDevice = _graphicsDevice;
	//m_Context->VSSetShader(m_VertexShader.Get(), nullptr, 0u);

	//Logger::PrintLog(Logger::PrintType::Success, "Vertex Shader has been successfully created.");

}

bool Engine::ShaderDevice::CompileShader(ComPtr<ID3DBlob>& Blob, string shaderName, ShaderType type)
{
	Logger::PrintLog(Logger::PrintType::Warning, "CompileShader() has no implemented method yet!");
	return false;
}

bool Engine::ShaderDevice::CompileVertexShader(ComPtr<ID3DBlob>& Blob)
{
	return false;
}

bool Engine::ShaderDevice::CompilePixelShader(ComPtr<ID3DBlob>& Blob)
{
	return false;
}
