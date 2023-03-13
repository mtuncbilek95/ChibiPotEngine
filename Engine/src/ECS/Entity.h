#pragma once

#include <Core/Types.h>

#include <ECS/EntityCore.h>
#include <ECS/EntityBase.h>
#include <ECS/Component.h>

class Entity {
public:
	Entity() {
		for (auto& el : m_ComponentList) {
			el = nullptr;
		}
	}
	virtual ~Entity() = default;

	inline void Update() {
		for (auto& el : m_Components) {
			el->Update();
		}
	}

	inline void Draw() {
		for (auto& el : m_Components) {
			el->Draw();
		}
	}

	template<typename T, typename... TArgs>
	inline T& AddComponent(TArgs&&... args) {
		T* component = new T(args...);

		std::unique_ptr<Component> cPtr{ component };
		m_Components.emplace_back(std::move(cPtr));

		if (component->Initialize()) {
			m_ComponentList[EntityBase::GetComponentTypeID<T>()] = component;
			m_ComponentBitset[EntityBase::GetComponentTypeID<T>()] = true;
			component->SetEntity(this);
			return *component;
		}

		return *static_cast<T*>(nullptr);
	}

	template<typename T>
	inline T& GetComponent() const {
		auto cPtr{ m_ComponentList[EntityBase::GetComponentTypeID<T>()] };
		return *cPtr;
	}

	template<typename T>
	inline bool HasComponent() const {
		return m_ComponentBitset[EntityBase::GetComponentTypeID<T>()];
	}

	inline bool HasAnyComponent() const {
		return m_ComponentBitset.any();
	}

	inline bool IsActive() const {
		return bIsActive;
	}

	inline void Destroy() {
		bIsActive = false;
	}

private:
	std::vector<std::unique_ptr<Component>> m_Components;

	ComponentArray m_ComponentList;
	ComponentBitset m_ComponentBitset;

private:
	bool bIsActive = true;
};