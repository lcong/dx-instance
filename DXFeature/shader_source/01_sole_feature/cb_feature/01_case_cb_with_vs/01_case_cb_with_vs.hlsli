
cbuffer ConstanBuffer : register(b0)
{
    float4 light;
}

struct VertexIn
{
    float4 pos : POSITION;
    float4 color : COLOR;    
};

struct VertexOut
{
    float4 posH : SV_POSITION;
    float4 color : COLOR;
};