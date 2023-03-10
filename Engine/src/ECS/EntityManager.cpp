#include "EntityManager.h"

#include <ECS/Entity.h>

void EntityManager::Update()
{
	for (auto& el : m_Entities) el->Update();
}

void EntityManager::Draw()
{
	for (auto& el : m_Entities) el->Draw();
}

void EntityManager::Refresh()
{
}

void EntityManager::AddEntity(Entity* newEntity)
{
	std::unique_ptr<Entity> e_Ptr{ newEntity };
	m_Entities.push_back(e_Ptr);
}

void EntityManager::RemoveEntity(Entity* targetEntity)
{
}

Entity* EntityManager::DuplicateEntity(Entity* targetEntity)
{
	return nullptr;
}
