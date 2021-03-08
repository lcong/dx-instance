#include "03_case_texture_2d_array_rgba8.hlsli"

float4 PS(VertexOut pIn):SV_Target
{
    return gTexArr.SampleLevel(gSamLinear, float3(pIn.tex, pIn.tex.x), 0.0f);
}
        