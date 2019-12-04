cbuffer MatrixBuffer : register(b0)
{
    matrix world;
    matrix view;
    matrix proj;
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
};

OutputType main(InputType input)
{
    OutputType output;
    
    output.position = mul(input.position, world);
    output.position = mul(output.position, view);
    output.position = mul(output.position, proj);
    
    output.tex = input.tex;
    
    return output;
}