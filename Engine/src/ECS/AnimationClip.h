#pragma once

#include <Core/CoreMinimal.h>
#include <ECS/EntityCore.h>

class Sprite;

class AnimationClip {
public:
	AnimationClip(string clipName, int desiredSpeed) : m_AnimationName(clipName), m_DesiredSpeed(desiredSpeed) {

	}

	string GetName() { return m_AnimationName; }
private:
	string m_AnimationName;
	std::unordered_map<XMFLOAT2, Sprite*> m_Sprites;
	int m_DesiredSpeed;
};