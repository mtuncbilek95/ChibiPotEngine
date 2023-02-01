#pragma once
#include <Core/CoreMinimal.h>

struct VertexData {
	XMFLOAT3 VertexPoint;
	XMFLOAT4 Color;
};

struct ConstantBuffer
{
	XMMATRIX transform;
};