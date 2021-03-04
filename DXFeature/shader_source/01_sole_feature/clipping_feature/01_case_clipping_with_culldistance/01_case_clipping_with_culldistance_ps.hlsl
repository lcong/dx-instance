#include "01_case_clipping_with_culldistance.hlsli"

float4 PS(VertexOut pIn):SV_Target
{ 
    return pIn.color;
}
