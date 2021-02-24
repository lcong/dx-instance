---
typora-root-url: picture
---

# Attribute Interpolation Feature

## 01:case noperspective interpolation

### 用例输入：

![02_case_linear_interpolation_vs_input](/02_case_linear_interpolation_vs_input.png)



```
如上，vs输入数据为三组positon以及color,绘制模式为triangle_list，设置color 插值属性为linear
```



### 处理流程：

```mermaid
graph TD;
	start-->A[ShowWindow];
	A-->B[D3D11CreateDevice];
	B-->C[CreateSwapChain];
	C-->D[context->OMSetRenderTargets];
	D-->E[context->RSSetViewports];
	E-->I[contest->IASetVertexBuffers];
	I-->F[context->ClearRenderTargetView];
	F-->G[context->draw];
	G-->H[swapchain->present]
	
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
    linear float4 color : COLOR;
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

![02_case_linear_interpolation_vs_input](/02_case_linear_interpolation_vs_input.png)



![02_case_linear_interpolation_result](/02_case_linear_interpolation_result.png)



```
如上，最终窗口会有rgb三色三角形绘制
```

