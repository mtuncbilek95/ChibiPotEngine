#include "Shader.h"

Shader::Shader(ComPtr<ID3D11DeviceContext>& context, ComPtr<ID3D11Device>& device) : m_Context(context), m_Device(device)
{
}

bool Shader::CompileShader(string shaderName, ShaderType type)
{
    return false;
}
