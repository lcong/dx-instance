#include "01_case_clipping_with_culldistance.hlsli"

VertexOut VS (VertexIn vIn)
{
    VertexOut vOut;
    vOut.pos = vIn.pos;
    vOut.color = vIn.color;
    vOut.culldistance = vIn.culldistance;//����ֱ�Ӷ���û���Զ���plane,ֱ������culldistance�ľ���ֵ
    return vOut;
}
