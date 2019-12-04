struct InputType
{
    float4 pos : sv_position;
    float2 tex : texcoord0;
    float4 depth : texcoord1;
};

float4 main(InputType input) : sv_target
{
    float depthValue = input.depth.z / input.depth.w;
    
    return float4(depthValue, depthValue, depthValue, 1);
    
}