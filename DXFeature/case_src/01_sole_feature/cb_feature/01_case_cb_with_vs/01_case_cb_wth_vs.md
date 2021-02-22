---
typora-root-url: picture
---

# Cb Feature

## 01:case cb with vs

### 用例输入：

![01_case_cb_with_vs_vs_input](/01_case_cb_with_vs_vs_input.png)



```
如上，vs输入数据为三组positon以及color,绘制模式为triangle_list
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
	I-->J[context->VSSetConstantBuffers];
	J-->F[context->ClearRenderTargetView];
	F-->G[context->draw];
	G-->H[swapchain->present]
	
```



```hlsl
inc:
cbuffer ConstanBuffer : register(b0)
{
    float4 light;
}

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
    vOut.color = light;
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

![01_case_cb_with_vs_vs_output](/01_case_cb_with_vs_vs_output.png)



![01_case_cb_with_vs_result](/01_case_cb_with_vs_result.png)



```
如上，最终窗口会有绿色三角形绘制。
```

