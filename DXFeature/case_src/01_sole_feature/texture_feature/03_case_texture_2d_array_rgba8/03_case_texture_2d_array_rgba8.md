---
typora-root-url: picture

---

# Texture Feature

## 03:case texture 2d array rgba8

### 用例输入：

![03_case_texture2d_array_vertex_input](/03_case_texture2d_array_vertex_input.png)



![03_case_texture2d_array_rgba8_input_array1](/03_case_texture2d_array_rgba8_input_array1.png)



![03_case_texture2d_array_rgba8_input_array2](/03_case_texture2d_array_rgba8_input_array2.png)



```
如上，vs输入数据为六组positon以及color和texcoord,绘制模式为triangle_list，并有texture array 2输入
```

### 处理流程：

```mermaid
graph TD;
	start-->A[ShowWindow];
	A-->B[D3D11CreateDevice];
	B-->C[CreateSwapChain];
	C-->D[context->OMSetRenderTargets];
	D-->E[context->RSSetViewports];
	E-->L[context->CreateTexture2D];
	L-->I[context->IASetVertexBuffers];
	I-->J[context->PSSetShaderResources];
	J-->K[context->PSSetSamplers];
	K-->F[context->ClearRenderTargetView];
	F-->G[context->drawindex];
	G-->H[swapchain->present]
	
```



```hlsl
inc:
Texture2DArray gTexArr : register(t0);

SamplerState gSamLinear : register(s0);

struct VertexIn
{
    float4 pos : POSITION;
    float4 color : COLOR; 
    float2 tex : TEXCOORD;
};

struct VertexOut
{
    float4 posH : SV_POSITION;
    float4 color : COLOR;
    float2 tex : TEXCOORD;
};

```

```hlsl
vs_src:
VertexOut VS(VertexIn vIn)
{
    VertexOut vOut;
    vOut.posH = vIn.pos;
    vOut.color = vIn.color;
    vOut.tex = vIn.tex;
    return vOut;
}
```

```hlsl
ps_src:
float4 PS(VertexOut pIn):SV_Target
{
    return gTexArr.SampleLevel(gSamLinear, float3(pIn.tex, pIn.tex.x), 0.0f);
}
```



### 预期输出：

![03_case_texture2d_array_vertex_output](/03_case_texture2d_array_vertex_output.png)



![03_case_texture2d_array_rgba8_result](/03_case_texture2d_array_rgba8_result.png)



```
如上，会有texture array 中的纹理混合输出，输出纹理左边是array0的纹理，右边是arrar1的纹理
```

