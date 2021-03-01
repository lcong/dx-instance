#include "01_case_draw_instance.hlsli"

VertexOut VS(VertexIn vIn,uint InstanceId :SV_InstanceID)
{
    VertexOut vOut;
    vOut.posH = float4(vIn.pos.x + (vIn.offset.x * InstanceId),
                       vIn.pos.y + (vIn.offset.y * InstanceId),
                       vIn.pos.zw);
    vOut.color = vIn.color;
    return vOut;
}
