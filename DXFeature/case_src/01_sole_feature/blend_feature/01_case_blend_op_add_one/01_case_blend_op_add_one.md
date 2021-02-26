---
typora-root-url: picture

---

# Draw Mode Feature

## 01:case draw_triangle

### 用例输入：

![01_case_blend_op_add_one_vs_input](/01_case_blend_op_add_one_vs_input.png)

```
如上，vs输入数据为三组positon以及color,绘制模式为triangle_list,一共会调用draw 两次，并且使能混合模式
```



### 处理流程：

```mermaid
graph TD;
	start-->A[ShowWindow];
	A-->B[D3D11CreateDevice];
	B-->C[CreateSwapChain];
	C-->D[context->OMSetRenderTargets];
	D-->E[context->RSSetViewports];
	E-->I[context->IASetVertexBuffers:1];
	I-->J[context->OMSetBlendState];
	J-->F[context->ClearRenderTargetView];
	F-->G[context->draw];
	G-->K[context->IASetVertexBuffers:2];
	K-->L[contex->draw];
	L-->H[swapchain->present]
	
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

### 预期输出：

![01_case_blend_op_add_one_vs_output](/01_case_blend_op_add_one_vs_output.png)



![01_case_blend_op_add_one_result](/01_case_blend_op_add_one_result.png)



```
如上，最终会有红绿两色三角形绘制，重叠处混合颜色为黄色
```

