#pragma once
#include <Core/CoreMinimal.h>

struct VertexData {
	XMFLOAT3 VertexPoint;
	XMCOLOR4 Color;
};

struct ConstantBuffer
{
	XMMATRIX transform;
};