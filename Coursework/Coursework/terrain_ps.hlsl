Texture2D depthMap : register(t0);
SamplerState depthSampler : register(s0);
Texture2D heightMap : register(t1);
SamplerState heightSampler : register(s1);


cbuffer LightBuffer : register(b0)
{
    float4 ambient;
    float4 diffuse;
    float3 direction;
    float3 lpos;
    float lpadding;
}

struct InputType
{
    float4 pos : sv_position;
    float2 tex : texcoord0;
    float3 normal : normal;
    float4 lightViewPos : texcoord1;
};

float4 lighting(float3 normal)
{
    float intensity = saturate(dot(normal, -direction)) + ambient;
    float4 colour = intensity;      
    return colour;    
}

float4 main(InputType input) : sv_target
{
    float depthValue;
    float lightDepthValue;
    float bias = 0.005f;
    float4 colour = float4(0, 0, 0, 1);
    
    
    float2 pTex = input.lightViewPos.xy / input.lightViewPos.w;
    pTex *= float2(0.5, -0.5);
    pTex += float2(0.5, 0.5);
    
    if (pTex.x < 0.0f || pTex.x > 1.0f || pTex.y < 0.0f || pTex.y > 1.0f)
        return float4(1, 0, 0, 1);

    depthValue = depthMap.Sample(depthSampler, pTex).r;
    
    lightDepthValue = input.lightViewPos.z / input.lightViewPos.w;
    lightDepthValue -= bias;
    
    if (lightDepthValue < depthValue)
        colour = lighting(input.normal);
    
    float4 tex = heightMap.Sample(heightSampler, input.tex);
    
    if (tex.r > 0.05f)
        colour *= tex;
    else
        colour *= 0.05f;
    
    return colour;
}