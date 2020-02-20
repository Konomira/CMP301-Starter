cbuffer MatrixBuffer : register(b0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
}

struct InputType
{
	float4 position: POSITION;
	float4 colour : COLOR;
};

struct OutputType
{
	float4 position :SV_POSITION;
	float4 colour : COLOR;
};

OutputType main(InputType input)
{
	OutputType output;

	input.position.w = 1.0f;


	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.colour = input.colour;

	return output;
}