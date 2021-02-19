#include "01_case_cb_with_vs.hlsli"

VertexOut VS(VertexIn vIn)
{
    VertexOut vOut;
    vOut.posH = vIn.pos;
    vOut.color = light;
    return vOut;
}
