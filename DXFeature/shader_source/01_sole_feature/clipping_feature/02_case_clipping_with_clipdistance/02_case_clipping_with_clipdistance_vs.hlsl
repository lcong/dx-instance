#include "02_case_clipping_with_clipdistance.hlsli"

VertexOut VS (VertexIn vIn)
{
    VertexOut vOut;
    vOut.pos = vIn.pos;
    vOut.color = vIn.color;
    vOut.clipdistance = vIn.clipdistance;//这里直接定义没有自定义plane,直接设置clipdistance的绝对值
    return vOut;
}
