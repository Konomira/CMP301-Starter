Texture2D t0 : register(t0);
SamplerState s0 : register(s0);

struct InputType
{
    float4 position : sv_position;
    float2 tex : texcoord0;
};

float4 main(InputType input) : sv_target
{
    return t0.Sample(s0, input.tex);    
}