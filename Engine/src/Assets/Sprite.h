#pragma once

#include <Core/CoreMinimal.h>

class TextureObject;
class ShaderObject;

class Sprite {
public:
	Sprite(XMINT2 locPoint, TextureObject* texture, ShaderObject* shader) {
		m_Texture = texture;
		m_Shader = shader;
		m_Texture->InitializeTexture(locPoint);
	}
private:
	TextureObject* m_Texture;
	ShaderObject* m_Shader;
};