Texture2D t0 : register(t0);
SamplerState s0 : register(s0);

struct InputType
{
	float4 position : SV_POSITION;
	float4 tex: TEXCOORD0;
};

float4 main(InputType input) : SV_TARGET
{
	float4 textureColour;
	float sampleColour = t0.Sample(s0, input.tex).r;
	if (sampleColour <= 0.25f)
		textureColour = float4(0.65f, 0.7f, 0.0f, 1.0f);
	else if (sampleColour <= 0.5f)
		textureColour = float4(0.5f, 0.5f, 0.5f, 1.0f);
	else
		textureColour = float4(1.0f, 1.0f, 1.0f, 1.0f);

	textureColour += sampleColour - 0.5f;

	return textureColour;
}