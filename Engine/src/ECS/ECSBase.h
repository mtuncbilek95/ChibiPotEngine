#pragma once

#include <Core/Types.h>
#include <ECS/ECSCore.h>

class Component;
class Entity;

using ComponentID = std::size_t;

ComponentID GetComponentTypeID() {
	static ComponentID lastID = 0;
	return lastID++;
}

template<typname T>
ComponentID GetComponentTypeID() noexcept {
	static ComponentID typeID = GetComponentID();
	return typeID;
}

constexpr std::size_t MaxComponents = 32;

using ComponentBitset = std::bitset<MaxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;