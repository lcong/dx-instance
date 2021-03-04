#include "02_case_stream_output_with_patch_list.hlsli"

VertexOut VS(VertexIn vIn)
{
    VertexOut vOut;
    vOut.pos = vIn.pos;
    return vOut;
}
