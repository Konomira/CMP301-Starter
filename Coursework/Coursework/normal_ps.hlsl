struct InputType
{
    float4 position : SV_POSITION;
    float4 tex : TEXCOORD0;
    float3 normal : normal;
};

float4 main(InputType input) : SV_TARGET
{
    
    return float4(input.normal.x, input.normal.y, input.normal.z, 1.0);
}