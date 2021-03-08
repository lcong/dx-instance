#include "05_case_texture_cube_array_rgba8.hlsli"

float4 PS(VertexOut pIn):SV_Target
{    
    return gTexCubeArr.Sample(gSamLinear, float4(pIn.cubePos.xyz,pIn.instanceId));
}