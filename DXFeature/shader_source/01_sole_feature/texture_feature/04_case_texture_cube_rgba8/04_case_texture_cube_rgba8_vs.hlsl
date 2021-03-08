#include "04_case_texture_cube_rgba8.hlsli"

VertexOut VS(VertexIn vIn)
{
    VertexOut vOut;
    vOut.posH = mul(vIn.pos, modelMat);
    vOut.posH = mul(vOut.posH, viewMat);
    vOut.posH = mul(vOut.posH, projectMat);    
    vOut.cubePos = float3(vIn.pos.xyz);
    vOut.color = vIn.color;
    return vOut;
}
