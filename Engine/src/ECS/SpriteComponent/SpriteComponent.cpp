#include "SpriteComponent.h"
#include <Logger/Logger.h>

//#define STB_IMAGE_IMPLEMENTATION
//#include <ImageLoader/stb_image.h>

SpriteComponent::SpriteComponent(uint32 width, uint32 height) : spriteWidth(width), spriteHeight(height),
totalWidth(0), totalHeight(0), tileSize(0)
{

}

void SpriteComponent::InitializeSprite(string atlasPath)
{
	/*int imageChannels{}, imageDesiredChannels{ 4 };
	string filePath = Logger::GetInitialDir() + atlasPath;
	const byte* ImageData = stbi_load(filePath.c_str(), &totalWidth, &totalHeight, &imageChannels, imageDesiredChannels);*/
}

void SpriteComponent::PlayAnimation()
{
}

uint32 SpriteComponent::GetWidth() { return spriteWidth; }
uint32 SpriteComponent::GetHeight() { return spriteHeight; }
