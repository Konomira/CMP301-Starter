Texture2D heightMap : register(t0);
SamplerState heightSampler : register(s0);

cbuffer MatrixBuffer : register(b0)
{
    matrix world;
    matrix view;
    matrix projection;
}

cbuffer HeightBuffer : register(b1)
{
    float4 scale;
    float4 heightOffset;
}

cbuffer CameraBuffer : register(b2)
{
    float3 pos;
    float padding;
}

struct InputType
{
    float4 pos : POSITION;
    float2 tex : texcoord0;
};

struct OutputType
{
    float4 pos : sv_position;
    float2 tex : texcoord0;
    float4 depth : texcoord1;
};

OutputType main(InputType input)
{
    OutputType output;
    input.pos.w = 1.0f;
    output.pos = input.pos;
    
    if (heightMap.SampleLevel(heightSampler, input.tex, 0).r > 0.05f)
        output.pos.y += (heightMap.SampleLevel(heightSampler, input.tex, 0).r * scale.x);//    -heightOffset.x;
    
    output.pos = mul(output.pos, world);
    
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    output.depth = output.pos;
    output.tex = input.tex;    
    return output;
}