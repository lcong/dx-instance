#include "01_case_stream_output.hlsli"

float4 PS(VertexOut pIn):SV_Target
{    
    return pIn.color;
}