#include "02_case_stream_output_with_patch_list.hlsli"

float4 PS(float4 pos :SV_Position ):SV_Target
{    
    return float4(1.0f, 0.0f, 0.0f, 1.0f);
}