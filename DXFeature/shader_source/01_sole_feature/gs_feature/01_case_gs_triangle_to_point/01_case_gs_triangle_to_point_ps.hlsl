#include "01_case_gs_triangle_to_point.hlsli"

float4 PS(VertexOut pIn):SV_Target
{    
    return pIn.color;
}