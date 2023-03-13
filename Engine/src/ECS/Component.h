#pragma once

#include <Core/Types.h>

#include <ECS/EntityCore.h>
#include <ECS/Entity.h>

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
