#include "01_case_image_load_store.hlsli"

Texture2D gTex : register(t0);

RWTexture2D<float4 > gOutput : register(u1);

float4 PS(vertexOut pIn) :SV_Target
{    
    uint3 iLocation = uint3(pIn.texcoord.x *4,pIn.texcoord.y*4,0);
    
    float4 fragColor = gTex.Load(iLocation); 
    gOutput[iLocation.xy] = fragColor;
    return fragColor;
}