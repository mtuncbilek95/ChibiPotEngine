#pragma once

#include <Core/CoreMinimal.h>

#include <Assets/SpriteAnimation.h>

class SpriteComponent
{
public:
	SpriteComponent() = default;

public:
	virtual ~SpriteComponent() = default;

	/**
	 * @brief Adds the animation to the map via given name in order to call it via name
	 * in PlayAnimation function.
	 *
	 * @param atlasName The name of the animation in hashmap
	 * @param animationFile The file in hashmap
	 */
	void AddSpriteAnimation(string atlasName, SpriteAnimation animationFile);
	/**
	 * @brief Plays the added sprite state.
	 *
	 * @param stateName Chooses the animation that will be played.
	 * @param FPS Determines how many frames the animation plays in a second.
	 * @param DeltaTime deltaTime that comes from Update.
	 */
	void PlayAnimation(string stateName, float FPS, float DeltaTime);

private:
	std::unordered_map<string, SpriteAnimation> AnimationHashMap;
};