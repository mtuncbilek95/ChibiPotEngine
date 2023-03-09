#pragma once

#include <Core/Types.h>

#include <ECS/EntityCore.h>
#include <ECS/EntityBase.h>
#include <ECS/Component.h>

class Entity {
public:
	Entity() {}
	virtual ~Entity() {}

	void Update() {}
	void Draw() {}

	template<typename T, typename... TArgs>
	inline T& AddComponent(TArgs&&... args) {
		T* component(new T(std::forward<TArgs>(args)...));

		std::unique_ptr<Component> cPtr{ component };
		Components.emplace_back(std::move(cPtr));

		if (component->Initialize()) {
			m_ComponentList[GetComponentTypeID<T>()] = component;
			m_ComponentBitset[GetComponentTypeID<T>()] = true;
			component->Entity = this;
			return *component;
		}

		return *static_cast<T*>(nullptr);
	}

	template<typename T>
	inline T& GetComponent() const {
		auto cPtr{ m_ComponentList[GetComponentTypeID<T>()] };
		return *cPtr;
	}

	template<typename T>
	inline bool HasComponent() const {
		return m_ComponentBitset[GetComponentTypeID<T>()];
	}
private:
	std::vector<std::unique_ptr<Component>> Components;

	ComponentArray m_ComponentList;
	ComponentBitset m_ComponentBitset;
};