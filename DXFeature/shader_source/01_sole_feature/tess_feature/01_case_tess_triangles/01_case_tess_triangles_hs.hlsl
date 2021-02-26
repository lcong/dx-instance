#include "01_case_tess_triangles.hlsli"

[domain("tri")]
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("triConstantHS")]

float3 HS(InputPatch<VertexOut,3> patch, uint i : SV_OutputControlPointID, uint patchId : SV_PrimitiveID):POSITION
{
    return patch[i].posH;   
}