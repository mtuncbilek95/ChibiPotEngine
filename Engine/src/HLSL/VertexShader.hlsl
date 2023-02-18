struct pOut
{
	float4 pos : SV_Position;
	float2 uv: TEXCOORD0;
};

struct vOut {
	float3 pos : POSITION;
	float2 uv : TEXCOORD0;
};

cbuffer CBuffer
{
    float tilex;
};

pOut main(vOut input)
{
	pOut vso;
	vso.pos = float4(input.pos, 1.0f);
	vso.uv = input.uv;
    
    vso.uv.x += 6 * tilex;

	return vso;
}