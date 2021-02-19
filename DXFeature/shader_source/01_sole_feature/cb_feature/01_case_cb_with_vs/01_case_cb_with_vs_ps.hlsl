#include "01_case_cb_with_vs.hlsli"

float4 PS(VertexOut pIn):SV_Target
{    
    return pIn.color;
}