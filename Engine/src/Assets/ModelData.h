#pragma once
#include <Core/CoreMinimal.h>

struct VertexData {
	XMFLOAT3 VertexPoint;
	XMUCHAR4 Color;
};

struct ConstantBuffer
{
	XMMATRIX transform;
};