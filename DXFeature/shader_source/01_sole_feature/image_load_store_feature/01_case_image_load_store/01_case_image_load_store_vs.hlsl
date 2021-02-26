#include "01_case_image_load_store.hlsli"

vertexOut VS(vertexIn pIn)
{
    vertexOut vOut;
    vOut.color = pIn.color;
    vOut.pos = pIn.pos;
    vOut.texcoord = pIn.texcoord;
    
    return vOut;
}
