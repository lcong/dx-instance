#include "01_case_draw_triangle.hlsli"

float4 PS(VertexOut pIn):SV_Target
{    
    return pIn.color;
}