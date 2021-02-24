#include "01_case_noperspective_interpolation.hlsli"

float4 PS(VertexOut pIn):SV_Target
{    
    return pIn.color;
}