#include "01_case_4mrt.hlsli"

psOut PS(VertexOut pIn)
{   
    psOut pOut;
    pOut.fragColor0 = float4(0.0f, 1.0f, 0.0f, 1.0f);
    pOut.fragColor1 = float4(0.0f, 0.0f, 1.0f, 1.0f);
    pOut.fragColor2 = float4(0.0f, 1.0f, 1.0f, 1.0f);
    pOut.fragColor3 = pIn.color;
    return pOut;
}