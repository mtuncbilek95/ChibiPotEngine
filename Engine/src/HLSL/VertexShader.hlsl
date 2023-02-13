struct pOut
{
	float4 pos : SV_Position;
	float2 tex: TEXCOORD0;
};

struct vOut {
	float3 pos : POSITION;
	float2 tex : TEXCOORD0;
};

//cbuffer MatrixBuffer
//{
//	matrix worldMatrix;
//	matrix viewMatrix;
//	matrix projectionMatrix;
//};

pOut main(vOut input)
{
	pOut vso;
	vso.pos = float4(input.pos, 1.0f);
	vso.tex = input.tex;

	return vso;
}