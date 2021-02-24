Texture2D g_Tex : register(t0);

RWTexture2D<unorm float4> g_Output : register(u0);
//1个线程组中线程个数
[numthreads(4,4,1)]

void CS(uint3 DTid:SV_DispatchThreadID)
{
    g_Output[DTid.xy] = g_Tex[DTid.xy];
}