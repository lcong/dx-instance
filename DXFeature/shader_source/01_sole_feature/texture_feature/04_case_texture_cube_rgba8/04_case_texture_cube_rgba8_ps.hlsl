#include "04_case_texture_cube_rgba8.hlsli"

float4 PS(VertexOut pIn):SV_Target
{    
    return gTexCube.Sample(gSamLinear, float3(pIn.cubePos.xyz));
}