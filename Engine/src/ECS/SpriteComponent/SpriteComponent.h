#pragma once

#include <Core/CoreMinimal.h>

#include <Assets/SpriteAnimation.h>

class SpriteComponent
{

public:
	SpriteComponent() = default;

public:
	virtual ~SpriteComponent() = default;

	void AddSpriteAnimation(string atlasName, SpriteAnimation spriteFile);
	/**
	 * @brief Plays the added sprite state.
	 *
	 * @param FPS Determines how many frames the animation plays in a second.
	 * @param stateName Chooses the animation that will be played.
	 */
	void PlayAnimation(float FPS, string stateName);

private:
	std::unordered_map<string, SpriteAnimation> AnimationHashMap;
};