#pragma once

#include <ECS/ECSCore.h>
#include <Math/Vector2.h>

class Entity;

class Component {
public:

	virtual bool Initialize() { return true; }
	virtual void Update() {}
	virtual void Draw() {}
	virtual ~Component() {}
	
	void SetEntity(Entity* value) { entity = value; }
	Entity* GetEntity() { return entity; }
private:
	Entity* entity;
};

class Transform : Component {
public:
	Transform(){}
	virtual ~Transform(){}

	bool Initialize() override final{
		Position.
	}

	CEMath::Vector2<float> Position;
	CEMath::Vector2<float> Scale;
	float Rotation;
};

class Sprite {
	uint32 textureID;
	uint32 textureWidth;
	uint32 textureHeight;
	uint32 spriteWidth;
	uint32 spriteHeight;
};