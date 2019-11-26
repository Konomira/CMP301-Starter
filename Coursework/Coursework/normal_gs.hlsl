cbuffer MatrixBuffer : register(b0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

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
};

float4 calculateNormal(float4 position[3])
{
    float3 n = normalize(cross(position[2].xyz - position[0].xyz, position[1].xyz - position[0].xyz));
    return float4(n.x, n.y, n.z, 1.0f);
}

float4 calculateCentroid(float4 p[3], float3 normal = float3(0, 0, 0))
{
    return float4(
    ((p[0].x + p[1].x + p[2].x) / 3.0f) + normal.x,
    ((p[0].y + p[1].y + p[2].y) / 3.0f) + normal.y,
    ((p[0].z + p[1].z + p[2].z) / 3.0f) + normal.z,
    1.0f
    );
}

[maxvertexcount(2)]
void main(triangle InputType input[3], inout LineStream<OutputType> stream)
{
  

    float4 positions[3];
    positions[0] = mul(input[0].position, worldMatrix);
    positions[1] = mul(input[1].position, worldMatrix);
    positions[2] = mul(input[2].position, worldMatrix);
    OutputType output;

    output.position = calculateCentroid(positions);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

    output.tex = input[0].tex;
    output.normal = calculateNormal(positions).xyz;
    stream.Append(output);

    output.position = calculateCentroid(positions, output.normal);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

    output.tex = input[0].tex;
    stream.Append(output);

    stream.RestartStrip();
  
}