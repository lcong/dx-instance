#include "01_case_texture_2d.hlsli"

float4 PS(VertexOut pIn):SV_Target
{    
//    return pIn.color;
    return gTex.Sample(gSamLinear, pIn.tex);
}