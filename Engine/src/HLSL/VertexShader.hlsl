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
    float2 tileIndex;
    float columnCount;
    float rowCount;
};

pOut main(vOut input)
{
	pOut vso;
	vso.pos = float4(input.pos, 1.0f);
	vso.uv = input.uv;
    
    float offsetx = 1.0f / columnCount;
    float offsety = 1.0f / rowCount;
    
    vso += float2(tileIndex.x * offsetx, tileIndex.y * offsety);
    
    vso.uv.x += tileIndex;

	return vso;
}