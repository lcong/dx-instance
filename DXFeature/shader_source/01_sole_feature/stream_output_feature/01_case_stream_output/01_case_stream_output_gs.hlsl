#include "01_case_stream_output.hlsli"

[maxvertexcount(3)]
void GS(triangle VertexOut input[3], inout PointStream<VertexOut> output)
{
    int i = 0;
    for (i = 0; i < 3;i++)
    {
        VertexOut element;
        element.color = input[i].color;
        element.posH = float4(input[i].posH.x + 0.1, input[i].posH.yzw);
        output.Append(element);        
    }
}
