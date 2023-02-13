#pragma once
#include <Core/CoreMinimal.h>

struct VertexData {
	XMFLOAT3 VertexPoint;
	XMFLOAT2 UV;
};

struct ConstantBuffer
{
	XMMATRIX Transform;
};

struct ModelMatrix {
	XMMATRIX WorldMatrix;
	XMMATRIX ViewMatrix;
	XMMATRIX ProjectionMatrix;
};