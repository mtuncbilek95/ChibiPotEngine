#pragma once

#include <ECS/EntityCore.h>

class Entity;

class EntityManager {
public:
	EntityManager() = default;
	~EntityManager() = default;

	void Update();
	void Draw();
	void Refresh();

	void AddEntity(Entity* newEntity);
	void RemoveEntity(Entity* targetEntity);
	Entity* DuplicateEntity(Entity* targetEntity);
	int GetTotalEntities() { return m_Entities.size(); }
private:
	std::vector<Entity*> m_Entities;
};