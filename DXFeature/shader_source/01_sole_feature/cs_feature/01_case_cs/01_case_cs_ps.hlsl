#include "01_case_cs.hlsli"

float4 PS(VertexOut pIn):SV_Target
{    
    return pIn.color;
}