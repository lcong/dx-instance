struct VertexIn
{
    float4 pos : POSITION;
    float4 color : COLOR;
    float clipdistance : CLIPDISTANCE;
};

struct VertexOut
{
    float4 pos : SV_Position;
    float4 color : COLOR;
    float clipdistance : SV_ClipDistance;
};