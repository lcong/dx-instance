---
typora-root-url: picture

---

# Stream Output Feature

## 02:case stream output with patch list

### 用例输入：

![02_case_stream_output_with_patch_list_draw1_vs_input](/02_case_stream_output_with_patch_list_draw1_vs_input.png)



![02_case_stream_output_with_patch_list_draw2_vs_input](/02_case_stream_output_with_patch_list_draw2_vs_input.png)





```
如上,draw共绘制两次，第一次使用 stream_output,输入模式设置为 D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST,第二次将stream_output 的输出再进行绘制一次,输入模式设置为D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,该测试是为了验证PRIMITIVE_TOPOLOGY 设置为PATCHLIST,对so接受数据的影响
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
	I-->Q[device->CreateGeometryShaderWithStreamOutput]
	Q-->J[context->GSSetShader];
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
};

struct VertexOut
{
    float4 pos : SV_Position;  
};
```

```hlsl
vs_src:
VertexOut VS(VertexIn vIn)
{
    VertexOut vOut;
    vOut.pos = vIn.pos;
    return vOut;
}
```

```hlsl
ps_src:
float4 PS(float4 pos :SV_Position ):SV_Target
{    
    return float4(1.0f, 0.0f, 0.0f, 1.0f);
}
```



### 预期输出：

![02_case_stream_output_with_patch_list_draw2_so_input](/02_case_stream_output_with_patch_list_draw2_so_input.png)



![02_case_stream_output_with_patch_list_draw2_vs_output](/02_case_stream_output_with_patch_list_draw2_vs_output.png)



![02_case_stream_output_with_patch_list_draw2_result](/02_case_stream_output_with_patch_list_draw2_result.png)



```
如上，最终窗口会有8个点绘制，说明有8个元素进入了so
```

