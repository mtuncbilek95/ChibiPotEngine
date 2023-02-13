Texture2D Tex2D;
SamplerState SampleType;

struct pOut {
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD0;
};

float4 main(pOut input) : SV_Target
{
	float4 texColor;
	texColor = Tex2D.Sample(SampleType, input.tex);

	return texColor;
}
