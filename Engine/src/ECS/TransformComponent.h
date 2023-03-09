#pragma once

#include <ECS/EntityCore.h>
#include <ECS/Component.h>

class TransformComponent : public Component {
public:
	TransformComponent() {
		Position = { 0.0f,0.0f,0.0f };
		Scale = { 1.0f,1.0f,1.0f };
		Rotation = 0.0f;
	}

	TransformComponent(XMFLOAT3 position, XMFLOAT3 scale, float rotation) {
		Position = position;
		Scale = scale;
		Rotation = rotation;
	}

	virtual ~TransformComponent() {}

	bool Initialize() override final {}

	XMFLOAT3 Position;
	XMFLOAT3 Scale;
	float Rotation;
};
