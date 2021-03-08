---
typora-root-url: picture

---

# Texture Feature

## 05:case texture cube array rgba8

### 用例输入：

![05_case_texture_cube_vertex_input](/05_case_texture_cube_vertex_input.png)

![05_case_texture_cube_rgba8_cube_x+](/05_case_texture_cube_rgba8_cube_x+.png)

![05_case_texture_cube_rgba8_cube_x-](/05_case_texture_cube_rgba8_cube_x-.png)



![05_case_texture_cube_rgba8_cube_y+](/05_case_texture_cube_rgba8_cube_y+.png)



![05_case_texture_cube_rgba8_cube_y-](/05_case_texture_cube_rgba8_cube_y-.png)

![05_case_texture_cube_rgba8_cube_z+](/05_case_texture_cube_rgba8_cube_z+.png)



![05_case_texture_cube_rgba8_cube_z-](/05_case_texture_cube_rgba8_cube_z-.png)





```
如上，vs输入数据为六组positon以及color和texcoord,绘制模式为triangle_list,以及输入为texture cube array3,各个array中的texture相同，如上为一个array中的六面cube数据,分别为x+,x-,y+,y-,z+,z-
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
	F-->G[context->DrawIndexedInstanced];
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

![05_case_texture_vertex_output](/05_case_texture_vertex_output.png)

![05_case_texture_cube_array_result](/05_case_texture_cube_array_result.png)



```
如上，三个cube绘制，
```

