cbuffer MatrixBuffer : register(b0)
{
    matrix world;
    matrix view;
    matrix ortho;
}

struct InputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
};

struct OutputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
};

OutputType main(InputType input)
{
    OutputType output;

    output.position = mul(input.position, world);
    output.position = mul(output.position, view);
    output.position = mul(output.position, ortho);

    output.tex = input.tex;

    return output;
}