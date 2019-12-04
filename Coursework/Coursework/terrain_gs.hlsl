cbuffer MatrixBuffer : register(b0)
{
    matrix world;
    matrix view;
    matrix proj;
    matrix lightView;
    matrix lightProj;
}

struct InputType
{
    float4 position : position;
    float2 tex : texcoord0;
};

struct OutputType
{
    float4 position : sv_position;
    float2 tex : texcoord0;
    float3 normal : normal;
    float4 lightViewPos : texcoord1;
};

float4 calculateNormal(float4 position[3])
{
    float3 n = normalize(cross(position[2].xyz - position[0].xyz, position[1].xyz - position[0].xyz));
    return float4(n.x, n.y, n.z, 1.0f);
}

[maxvertexcount(3)]
void main(triangle InputType input[3], inout TriangleStream<OutputType> stream)
{
    float4 positions[3];
    positions[0] = mul(input[0].position, world);
    positions[1] = mul(input[1].position, world);
    positions[2] = mul(input[2].position, world);
   
    
    for (int i = 0; i < 3; i++)
    {
        OutputType output;
        output.position = input[i].position;
        output.position = mul(output.position, world);
        output.position = mul(output.position, view);
        output.position = mul(output.position, proj);

        output.lightViewPos = positions[i];
        output.lightViewPos = mul(output.lightViewPos, lightView);
        output.lightViewPos = mul(output.lightViewPos, lightProj);
        
        output.tex = input[i].tex;
        output.normal = calculateNormal(positions).xyz;
        stream.Append(output);
    }
    stream.RestartStrip();
}