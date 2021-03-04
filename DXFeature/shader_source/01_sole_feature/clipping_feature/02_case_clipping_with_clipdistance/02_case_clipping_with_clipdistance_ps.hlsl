#include "02_case_clipping_with_clipdistance.hlsli"

float4 PS(VertexOut pIn):SV_Target
{ 
    return pIn.color;
}
