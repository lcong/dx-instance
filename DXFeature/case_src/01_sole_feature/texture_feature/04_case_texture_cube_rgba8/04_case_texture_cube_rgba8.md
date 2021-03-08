---
typora-root-url: picture

---

# Texture Feature

## 04:case texture cube rgba8

### 用例输入：

![04_case_texture_cube_rgba8_vertex_input](/04_case_texture_cube_rgba8_vertex_input.png)



![04_case_texture_cube_rgba8_cube_x+](/04_case_texture_cube_rgba8_cube_x+.png)

![04_case_texture_cube_rgba8_cube_x-](/04_case_texture_cube_rgba8_cube_x-.png)

![04_case_texture_cube_rgba8_cube_y+](/04_case_texture_cube_rgba8_cube_y+.png)

![04_case_texture_cube_rgba8_cube_y-](/04_case_texture_cube_rgba8_cube_y-.png)

![04_case_texture_cube_rgba8_cube_z+](/04_case_texture_cube_rgba8_cube_z+.png)

![04_case_texture_cube_rgba8_cube_z-](/04_case_texture_cube_rgba8_cube_z-.png)

```
如上，vs输入数据为六组positon以及color和texcoord,绘制模式为triangle_list，以及texture cube,分别为 x+,x-,y+,y-,z+,z-
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
TextureCube gTexCube : register(t0);
SamplerState gSamLinear : register(s0);

struct VertexIn
{
    float4 pos : POSITION;
    float4 color : COLOR; 
};

struct VertexOut
{
    float4 posH : SV_POSITION;
    float4 color : COLOR;
    float3 cubePos : POSITION;
};
cbuffer constantMat : register(b0)
{
    matrix modelMat;
    matrix viewMat;
    matrix projectMat;    
}

```

```hlsl
vs_src:
VertexOut VS(VertexIn vIn)
{
    VertexOut vOut;
    vOut.posH = mul(vIn.pos, modelMat);
    vOut.posH = mul(vOut.posH, viewMat);
    vOut.posH = mul(vOut.posH, projectMat);    
    vOut.cubePos = float3(vIn.pos.xyz);
    vOut.color = vIn.color;
    return vOut;
}
```

```hlsl
ps_src:
float4 PS(VertexOut pIn):SV_Target
{    
    return gTexCube.Sample(gSamLinear, float3(pIn.cubePos.xyz));
}

```



### 预期输出：

![04_case_texture_cube_rgba8_vertex_output](/04_case_texture_cube_rgba8_vertex_output.png)



![04_case_texture_cube_rgba8_result](/04_case_texture_cube_rgba8_result.png)



```
如上，会有cube绘制，各个面使用texture cube 对应面的纹理
```



