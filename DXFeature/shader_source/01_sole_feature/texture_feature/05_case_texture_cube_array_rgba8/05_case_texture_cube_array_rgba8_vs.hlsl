#include "05_case_texture_cube_array_rgba8.hlsli"

VertexOut VS(VertexIn vIn, uint instanceId:SV_InstanceID)
{
    VertexOut vOut;
    vOut.posH = float4(vIn.pos.x + vIn.offset.x, vIn.pos.yzw);
    vOut.posH = mul(vOut.posH, modelMat);
    vOut.posH = mul(vOut.posH, viewMat);
    vOut.posH = mul(vOut.posH, projectMat);    
    vOut.cubePos = float3(vIn.pos.xyz);
    vOut.color = vIn.color;
    vOut.instanceId = instanceId;
    return vOut;
}
