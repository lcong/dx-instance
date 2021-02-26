struct VertexIn
{
    float4 pos : POSITION;
    float4 color : COLOR;    
};

struct VertexOut
{
    float4 posH : SV_POSITION;
    float4 color : COLOR;
};

struct psOut
{
    float4 fragColor0 : SV_Target0;
    float4 fragColor1 : SV_Target1;
    float4 fragColor2 : SV_Target2;
    float4 fragColor3 : SV_Target3;    
};