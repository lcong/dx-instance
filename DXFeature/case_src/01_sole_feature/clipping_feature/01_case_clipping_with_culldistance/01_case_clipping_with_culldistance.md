---
typora-root-url: picture

---

# CLIPPINIG Feature

## 01:case clipping with culldistance

### 用例输入：

![01_case_clipping_with_culldistance_vs_input](/01_case_clipping_with_culldistance_vs_input.png)

```
如上，vs输入数据为6组positon以及color和culldistance,绘制模式为triangle_list，主要测试culldistance该系统变量的功能
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
    float culldistance : CULLDISTANCE;
};

struct VertexOut
{
    float4 pos : SV_Position;
    float4 color : COLOR;
    float culldistance : SV_CullDistance;
};
```

```hlsl
vs_src:
VertexOut VS (VertexIn vIn)
{
    VertexOut vOut;
    vOut.pos = vIn.pos;
    vOut.color = vIn.color;
    vOut.culldistance = vIn.culldistance;//这里直接定义没有自定义plane,直接设置culldistance的绝对值
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

![01_case_clipping_with_culldistance_vs_output](/01_case_clipping_with_culldistance_vs_output.png)



![01_case_clipping_with_culldistance_result](/01_case_clipping_with_culldistance_result.png)



```
如上，最终窗口只会有绿色三角形绘制,红色三角形由于组成图元的三个顶点的culldistance < 0,在rs阶段被丢弃，vs 输出的sv_CullDistance的值可能显示有问题，不应该为0
```

