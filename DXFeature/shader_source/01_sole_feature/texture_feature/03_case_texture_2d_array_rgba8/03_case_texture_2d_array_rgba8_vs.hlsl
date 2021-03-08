#include "03_case_texture_2d_array_rgba8.hlsli"

VertexOut VS(VertexIn vIn)
{
    VertexOut vOut;
    vOut.posH = vIn.pos;
    vOut.color = vIn.color;
    vOut.tex = vIn.tex;
    return vOut;
}
