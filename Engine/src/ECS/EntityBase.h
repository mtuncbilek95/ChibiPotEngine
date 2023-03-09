#pragma once

#include <Core/CoreMinimal.h>
#include <Core/Types.h>
#include <ECS/EntityCore.h>

class Component;
class Entity;

using ComponentID = std::size_t;

ComponentID GetUniqueComponentTypeID() {
	static ComponentID lastID = 0;
	return lastID++;
}

template<typename T>
ComponentID GetComponentTypeID() noexcept {
	static ComponentID typeID = GetUniqueComponentTypeID();
	return typeID;
}

constexpr std::size_t MaxComponents = 32;
constexpr std::size_t MaxEntities = 5000;

using ComponentBitset = std::bitset<MaxComponents>;
using ComponentArray = std::array<Component*, MaxEntities>;