---
typora-root-url: picture

---

# CS Feature

## 01:case cs

### 用例输入：

![01_case_cs_texture_input](/01_case_cs_texture_input.png)



```
如上,cs的输入为4x4的texture
```



### 处理流程：

```mermaid
graph TD;
	start-->A[ShowWindow];
	A-->B[D3D11CreateDevice];
	B-->C[CreateSwapChain];
	C-->D[context->OMSetRenderTargets];
	D-->E[context->RSSetViewports];
	E-->I[contest->CSSetShaderResources];
	I-->F[context->CSSetShader];
	F-->G[context->CSSetUnorderedAccessViews];
	G-->J[context->Dispatch:1,1,1];
	J-->H[swapchain->present]
	
```







```hlsl
cs_src:
Texture2D g_Tex : register(t0);

RWTexture2D<unorm float4> g_Output : register(u0);
//1个线程组中线程个数
[numthreads(4,4,1)]

void CS(uint3 DTid:SV_DispatchThreadID)
{
    g_Output[DTid.xy] = g_Tex[DTid.xy];
}
```





### 预期输出：

![01_case_cs_uav_output](/01_case_cs_uav_output.png)





```
如上，uav中的数据是原样获取的texture_2d中的数据
```

