struct vertexIn
{
    float4 pos : POSITION;
    float4 color : COLOR;
    float2 texcoord : TEXCOORD;
};


struct vertexOut
{
    float4 pos : SV_Position;
    float4 color : COLOR;
    float2 texcoord : TEXCOORD;
};




