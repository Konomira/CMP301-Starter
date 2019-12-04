Texture2D depthMap : register(t0);
SamplerState depthSampler : register(s0);

struct InputType
{
    float4 position : sv_position;
    float2 tex : texcoord0;
};

float4 main(InputType input) : sv_target
{
    float4 colour = depthMap.Sample(depthSampler, input.tex);
    
    return colour;
}