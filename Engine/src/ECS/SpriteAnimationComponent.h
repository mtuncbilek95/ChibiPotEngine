#pragma once

#include <Core/CoreMinimal.h>

#include <ECS/EntityCore.h>
#include <ECS/Component.h>

#include <ECS/AnimationClip.h>

class SpriteAnimationComponent : public Component {
public:
	SpriteAnimationComponent() : Component() {}
	~SpriteAnimationComponent() {}

	virtual bool Initialize() override {}
	virtual void Update() override {}
	virtual void Draw() override {}

	void AddClip(AnimationClip* clip) {
	
		m_AnimClip[clip->GetName()] = clip;
	}

	void Play(string clipName) {
		AnimationClip& search = m_AnimClips.find(clipName);
		search->second;
	}
private:
	std::unordered_map<string, AnimationClip> m_AnimClips;
};