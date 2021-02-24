#include "02_case_texture_2d_rgba8.hlsli"

float4 PS(VertexOut pIn):SV_Target
{    
//    return pIn.color;
    return gTex.Sample(gSamLinear,pIn.tex);
}