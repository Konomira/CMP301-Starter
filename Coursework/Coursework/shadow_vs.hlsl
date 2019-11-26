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
    float4 position : position;
    float2 tex : TEXCOORD0;
};

struct OutputType
{
    float4 position : POSITION;
    float4 depthPosition : TEXCOORD0;
};

OutputType main(InputType input)
{
    OutputType output;
    output.position = mul(input.position, worldMatrix);
    if (t0.SampleLevel(s0, input.tex, 0).r > 0.05f)
        output.position.y += (t0.SampleLevel(s0, input.tex, 0).r * 50.0f);

    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);


    

    output.depthPosition = output.position;

    return output;
}