#pragma once

#include <Core/Types.h>

#include <ECS/EntityCore.h>

class Entity;

class Component {
public:
	Component() = default;
	virtual bool Initialize() { return true; }
	virtual void Update() {}
	virtual void Draw() {}
	virtual ~Component() = default;

	void SetEntity(Entity* value) { entity = value; }
	Entity* GetEntity() { return entity; }
private:
	Entity* entity;
};

class Sprite {
	uint32 textureID;
	uint32 textureWidth;
	uint32 textureHeight;
	uint32 spriteWidth;
	uint32 spriteHeight;
};
