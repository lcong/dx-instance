#include "01_case_stencil_notequal.hlsli"

// 顶点着色器
VertexOut VS(VertexIn vIn)
{
    VertexOut vOut;
    vOut.posH = vIn.pos;
    vOut.color = vIn.color; // 这里alpha通道的值默认为1.0
    return vOut;
}
