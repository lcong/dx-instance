#include "01_case_scissor_enable.hlsli"

float4 PS(VertexOut pIn):SV_Target
{    
    return pIn.color;
}