#include "02_case_clipping_with_clipdistance.hlsli"

VertexOut VS (VertexIn vIn)
{
    VertexOut vOut;
    vOut.pos = vIn.pos;
    vOut.color = vIn.color;
    vOut.clipdistance = vIn.clipdistance;//����ֱ�Ӷ���û���Զ���plane,ֱ������clipdistance�ľ���ֵ
    return vOut;
}
