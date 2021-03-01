#include "01_case_draw_instance.hlsli"

float4 PS(VertexOut pIn):SV_Target
{    
    return pIn.color;
}