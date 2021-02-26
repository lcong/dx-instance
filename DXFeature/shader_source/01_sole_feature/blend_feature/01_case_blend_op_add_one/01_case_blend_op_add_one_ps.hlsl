#include "01_case_blend_op_add_one.hlsli"

float4 PS(VertexOut pIn):SV_Target
{    
    return pIn.color;
}