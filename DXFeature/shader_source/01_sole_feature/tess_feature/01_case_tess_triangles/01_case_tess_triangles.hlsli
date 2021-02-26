struct VertexIn
{
    float3 pos : POSITION;  
};

struct VertexOut
{
    float3 posH : POSITION;
};

typedef VertexOut HullOut;

struct triPatchTess
{
    float edgeTess[3] : SV_TessFactor;
    float insideTess[1] : SV_InsideTessFactor;
};

triPatchTess triConstantHS(InputPatch<VertexOut, 3> patch, uint patchId : SV_PrimitiveID)
{
    triPatchTess pt;
    pt.edgeTess[0] = 2.0f;
    pt.edgeTess[1] = 2.0f;
    pt.edgeTess[2] = 2.0f;
    pt.insideTess[0] = 2.0f;
    return pt;
}