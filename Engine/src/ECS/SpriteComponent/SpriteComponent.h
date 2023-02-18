#pragma once

#include <Core/CoreMinimal.h>

class SpriteComponent {

public:
	SpriteComponent() = delete;
	SpriteComponent(uint32 width, uint32 height);

public:
	virtual ~SpriteComponent() = default;

	void InitializeSprite(string atlasPath = "/Game-Resource/King/Idle (96x96).png");
	void PlayAnimation();

	uint32 GetWidth();
	uint32 GetHeight();
	
protected:
	int32 spriteWidth, spriteHeight, totalWidth, totalHeight, tileSize;
};