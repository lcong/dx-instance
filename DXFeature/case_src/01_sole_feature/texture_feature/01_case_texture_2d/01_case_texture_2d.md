---
typora-root-url: picture

---

# Texture Feature

## 01:case texture 2d

### 用例输入：

![01_case_texuture_2d_vs_input](/01_case_texuture_2d_vs_input.png)



```
如上，vs输入数据为六组positon以及color和texcoord,绘制模式为triangle_list
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
	I-->J[context->PSSetShaderResources];
	J-->K[context->PSSetSamplers];
	K-->F[context->ClearRenderTargetView];
	F-->G[context->drawindex];
	G-->H[swapchain->present]
	
```



```hlsl
inc:
Texture2D gTex : register(t0);
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
    return gTex.Sample(gSamLinear, pIn.tex);
}

```







### 预期输出：

![01_case_texture_2d_vs_output](/01_case_texture_2d_vs_output.png)





![01_case_texture_2d_result](/01_case_texture_2d_result.png)



```
如上，会有木箱的纹理显示
```

