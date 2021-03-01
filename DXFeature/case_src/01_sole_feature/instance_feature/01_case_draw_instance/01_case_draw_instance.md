---
typora-root-url: picture

---

# Draw Mode Feature

## 01:case draw_triangle

### 用例输入：

![01_case_draw_instance_vs_input](/01_case_draw_instance_vs_input.png)



```
如上，vs输入数据为三组positon以及color和offset,绘制模式为triangle_list,一共绘制5份instance 
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
	F-->G[context->DrawInstanced];
	G-->H[swapchain->present]
	
```



```hlsl
inc:
struct VertexIn
{
    float4 pos : POSITION;
    float4 color : COLOR;  
    float3 offset : OFFSET;
};

struct VertexOut
{
    float4 posH : SV_POSITION;
    float4 color : COLOR;
};
```

```hlsl
vs_src:
VertexOut VS(VertexIn vIn,uint InstanceId :SV_InstanceID)
{
    VertexOut vOut;
    vOut.posH = float4(vIn.pos.x + (vIn.offset.x * InstanceId),
                       vIn.pos.y + (vIn.offset.y * InstanceId),
                       vIn.pos.zw);
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

![01_case_draw_instance_vs_output](/01_case_draw_instance_vs_output.png)

![01_case_draw_instance_result](/01_case_draw_instance_result.png)



```
如上，最终窗口会有5个三角形绘制
```

