---
typora-root-url: picture

---

# Depth Test Feature

## 01:case depth test enable

### 用例输入：

![01_case_depth_test_enable_vs_input](/01_case_depth_test_enable_vs_input.png)

```
如上，vs输入数据为六组positon以及color,绘制模式为triangle_list
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
	F-->J[context->ClearDepthStencilView];
	J-->G[context->draw];
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

![01_case_depth_test_enable_vs_output](/01_case_depth_test_enable_vs_output.png)



![01_case_depth_test_enable_result](/01_case_depth_test_enable_result.png)





```
如上，最终会有两个三角形绘制，像素重叠部分的颜色应为红色。
```

