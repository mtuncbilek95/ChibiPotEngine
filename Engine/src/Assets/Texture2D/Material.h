#pragma once

#include <Core/CoreMinimal.h>

class ShaderProgram;
class GraphicsProgram;

class Material
{
public:
    Material(GraphicsProgram& graphics, std::vector<ShaderProgram>& shader);
    
    /**
     * @brief Create a ID3D11PixelShader for related Material.
     * 
     * @param p_device  Reference parameter for DirectX Device
     * @param p_Blob    Reference parameter for Data Blob.
     * @return if returns false, material wont be initialized.
     */
    bool CreatePixelShader(ComPtr<ID3D11Device>& p_device , ComPtr<ID3DBlob>& p_Blob);
    
};