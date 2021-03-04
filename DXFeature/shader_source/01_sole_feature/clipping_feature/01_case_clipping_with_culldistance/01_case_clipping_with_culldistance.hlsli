struct VertexIn
{
    float4 pos : POSITION;
    float4 color : COLOR;
    float culldistance : CULLDISTANCE;
};

struct VertexOut
{
    float4 pos : SV_Position;
    float4 color : COLOR;
    float culldistance : SV_CullDistance;
};