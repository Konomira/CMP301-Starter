Texture2D t0 : register(t0);
SamplerState s0 : register(s0);

cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
}

struct InputType
{
	float4 position: POSITION;
	float2 tex : TEXCOORD0;
};

struct OutputType
{
	float4 position :SV_POSITION;
	float2 tex : TEXCOORD0;
};

OutputType main(InputType input)
{
	OutputType output;

	input.position.w = 1.0f;

	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);
	if(t0.SampleLevel(s0, input.tex, 0).r > 0.05f)
		output.position.y += (t0.SampleLevel(s0, input.tex, 0).r * 100.0f) - 25.0f;

	output.tex= input.tex;

	return output;
}