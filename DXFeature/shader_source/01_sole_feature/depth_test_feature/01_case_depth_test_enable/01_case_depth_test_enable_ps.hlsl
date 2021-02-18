#include "01_case_depth_test_enable.hlsli"

float4 PS(VertexOut pIn):SV_Target
{    
    return pIn.color;
}