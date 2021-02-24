#include "02_case_linear_interpolation.hlsli"

float4 PS(VertexOut pIn):SV_Target
{    
    return pIn.color;
}