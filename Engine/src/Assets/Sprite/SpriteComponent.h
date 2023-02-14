#pragma once

#include <Core/CoreMinimal.h>

class SpriteComponent {

public:
	SpriteComponent() = delete;
	SpriteComponent()

public:
	virtual ~SpriteComponent();
	virtual void DrawSprite();
	virtual void PlayAnimation();

protected:
	ComPtr<ID3D11BlendState> m_BlendState;
	ComPtr<ID3D11SamplerState> m_SamplerState;

	ComPtr<ID3D11Texture2D> m_TextureBuffer;
};