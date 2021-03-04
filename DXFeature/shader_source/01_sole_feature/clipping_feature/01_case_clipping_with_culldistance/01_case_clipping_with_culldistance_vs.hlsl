#include "01_case_clipping_with_culldistance.hlsli"

VertexOut VS (VertexIn vIn)
{
    VertexOut vOut;
    vOut.pos = vIn.pos;
    vOut.color = vIn.color;
    vOut.culldistance = vIn.culldistance;//这里直接定义没有自定义plane,直接设置culldistance的绝对值
    return vOut;
}
