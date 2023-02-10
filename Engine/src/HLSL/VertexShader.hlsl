struct vOut
{
	float3 color : Color;
	float2 uv: UV;
	float4 pos : SV_Position;
};

vOut main(float3 pos : Position, float2 uv : UV,  float3 color : Color)
{
	vOut vso;
	vso.pos = float4(pos, 1.0f);
	vso.uv = uv;
	vso.color = color;
	return vso;
}