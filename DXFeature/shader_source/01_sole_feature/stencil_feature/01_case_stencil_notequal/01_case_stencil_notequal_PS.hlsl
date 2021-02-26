#include "01_case_stencil_notequal.hlsli"

// 像素着色器
float4 PS(VertexOut pIn) : SV_Target
{
    return pIn.color;
}

