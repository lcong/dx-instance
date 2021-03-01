struct VertexIn
{
    float4 pos : POSITION;
    float4 color : COLOR;  
    float3 offset : OFFSET;
};

struct VertexOut
{
    float4 posH : SV_POSITION;
    float4 color : COLOR;
};