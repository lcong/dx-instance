
TextureCube gTexCube : register(t0);
SamplerState gSamLinear : register(s0);

struct VertexIn
{
    float4 pos : POSITION;
    float4 color : COLOR; 
};

struct VertexOut
{
    float4 posH : SV_POSITION;
    float4 color : COLOR;
    float3 cubePos : POSITION;
};


cbuffer constantMat : register(b0)
{
    matrix modelMat;
    matrix viewMat;
    matrix projectMat;    
}