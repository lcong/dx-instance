#include "01_case_tess_triangles.hlsli"

[domain("tri")]

float4 DS(triPatchTess patchTess, float3 weights : SV_DomainLocation, OutputPatch<HullOut, 3> tri) : SV_POSITION
{
    float3 dsOut = tri[0].posH * weights[0] +
                 tri[1].posH * weights[1] +
                 tri[2].posH * weights[2];
    return float4(dsOut, 1.0f);
}
