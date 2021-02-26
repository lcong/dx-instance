#include "01_case_tess_triangles.hlsli"

float4 PS(float4 PosH :SV_Position):SV_Target
{    
    return float4(1.0f,0.0f,0.0f,1.0f);
}