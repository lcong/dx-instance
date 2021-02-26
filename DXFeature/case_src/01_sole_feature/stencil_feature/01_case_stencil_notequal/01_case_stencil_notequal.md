---
typora-root-url: picture

---

# Stencil Test Feature

## 01:case stencil test notequal

### 用例输入：

![01_case_stencil_notequal_draw1_vs_input](/01_case_stencil_notequal_draw1_vs_input.png)



![01_case_stencil_notequal_draw2_vs_input](/01_case_stencil_notequal_draw2_vs_input.png)



```
如上，vs输入数据为三组positon以及color,绘制模式为triangle_list,一共会有两次draw调用,第一次draw调用允许更新模板缓冲值，将绘制部分的模板缓冲值设置为参考值，第二次draw调用禁止更新模板缓冲值，将参考值与模板缓冲值进行比较，不相等才通过模板测试。
```



### 处理流程：

```mermaid
graph TD;
	start-->A[ShowWindow];
	A-->B[D3D11CreateDevice];
	B-->C[CreateSwapChain];
	C-->D[context->OMSetRenderTargets];
	D-->E[context->RSSetViewports];
	E-->I[context->IASetVertexBuffers1];
	I-->J[context->OMSetDepthStencilState:wirteMask 0xff]
	J-->F[context->ClearRenderTargetView];
	F-->G[context->draw];
	G-->K[context->IASetVertexBuffers2];
	K-->L[context->OMSetDepthStencilState:wirteMask 0];
	L-->M[context->draw];
	M-->H[swapchain->present]
	
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

![01_case_stencil_notequal_draw1_vs_output](/01_case_stencil_notequal_draw1_vs_output.png)

![01_case_stencil_notequal_draw1_result](/01_case_stencil_notequal_draw1_result.png)



![01_case_stencil_notequal_draw2_vs_input](/01_case_stencil_notequal_draw2_vs_input.png)

![01_case_stencil_notequal_draw2_result](/01_case_stencil_notequal_draw2_result.png)



```
如上，最终窗口会有两个重叠部分的三角形绘制，重叠部分的颜色为红色。
```

