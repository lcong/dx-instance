---
typora-root-url: picture

---

# Stream Output Feature

## 01:case stream output

### 用例输入：

![01_case_stream_output_draw1_vs_input](/01_case_stream_output_draw1_vs_input.png)



![01_case_stream_output_draw2_vs_input](/01_case_stream_output_draw2_vs_input.png)



```
如上,draw共绘制两次，第一次使用 stream_output,第二次将stream_output 的输出再进行绘制一次
```



### 处理流程：

```mermaid
graph TD;
	start-->A[ShowWindow];
	A-->B[D3D11CreateDevice];
	B-->C[CreateSwapChain];
	C-->D[context->OMSetRenderTargets];
	D-->E[context->RSSetViewports];
	E-->I[context->IASetVertexBuffers];
	I-->J[context->GSSetShader];
	J-->K[context->SOSetTargets];
	K-->F[context->ClearRenderTargetView];
	F-->G[context->draw];
	G-->H[swapchain->present];
	H-->L[context->SOSetTargets:nullptr];
	L-->M[context->GSSetShader:nullptr];
	M-->N[context->IASetVertexBuffers];
	N-->O[context->draw];
	O-->P[swapchain->present];
	
	
```



```hlsl
inc:
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
```

```hlsl
vs_src:

VertexOut VS(VertexIn vIn)
{
    VertexOut vOut;
    vOut.posH = vIn.pos;
    vOut.color = vIn.color;
    return vOut;
}
```

```hlsl
ps_src:


float4 PS(VertexOut pIn):SV_Target
{    
    return pIn.color;
}
```

```
gs_src:
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
```



### 预期输出：

![01_caes_stream_output_draw2_vs_output](/01_caes_stream_output_draw2_vs_output.png)



![01_case_stream_output_draw1_gs_output](/01_case_stream_output_draw1_gs_output.png)



![01_case_stream_output_draw2_result](/01_case_stream_output_draw2_result.png)

```
如上，最终窗口会有红色三角形绘制。
```

