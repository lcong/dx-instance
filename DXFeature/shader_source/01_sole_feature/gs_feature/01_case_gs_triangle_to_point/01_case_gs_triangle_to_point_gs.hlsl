#include "01_case_gs_triangle_to_point.hlsli"

[maxvertexcount(3)]
void GS(triangle VertexOut input[3], inout PointStream<VertexOut> output)
{
    
    int i = 0;
    for (i = 0; i < 3;i++)
    {
        VertexOut element;
        element.color = input[i].color;
        element.posH = input[i].posH;
        output.Append(element);
    }
}
