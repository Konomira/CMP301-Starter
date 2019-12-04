Texture2D t0 : register(t0);
SamplerState s0 : register(s0);

cbuffer HeightBuffer : register(b0)
{
    float4 scale;
    float4 heightOffset;
}

struct InputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
};

struct OutputType
{
    float4 position : POSITION;
};



OutputType main(InputType input)
{
    OutputType output;

    input.position.w = 1.0f;

    //output.position = mul(input.position, worldMatrix);
    //output.position = mul(output.position, viewMatrix);
    //output.position = mul(output.position, projectionMatrix);
    output.position = input.position;
    // If heightmap value is above the threshold, scale vertically with height offset
    if (t0.SampleLevel(s0, input.tex, 0).r > 0.05f)
        output.position.y += (t0.SampleLevel(s0, input.tex, 0).r * scale.x) - heightOffset.x;

    

    return output;
}