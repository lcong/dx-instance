#include "CaseApp.h"
#include "d3dUtil.h"
#include "DXTrace.h"
#include "filesystem.h"
#include "DDSTextureLoader.h"
#include "WICTextureLoader.h"
#include <sstream>


const D3D11_INPUT_ELEMENT_DESC CaseApp::VertexPosColor::inputLayout[3] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{"OFFSET",0,DXGI_FORMAT_R32G32B32_FLOAT,1,0,D3D11_INPUT_PER_INSTANCE_DATA,1}
};

CaseApp::CaseApp(HINSTANCE hInstance)
	: D3DApp(hInstance)
{
	m_MainWndCaption = L"05_case_texture_cube_array_rgba8";
	m_EnableDebug = false;
	m_EnableDepthTest = true;
	//m_setSize = 64;
}

unsigned char data[6][4096][4];

CaseApp::~CaseApp()
{
}

bool CaseApp::Init()
{
	if (!D3DApp::Init())
		return false;
	initEffect();
	initResource();
	return true;
}

bool CaseApp::initEffect()
{
	ComPtr<ID3DBlob> blob;
	std::wstringstream vsCsoFileWss;
	std::wstringstream vsFileWss;
	std::string vsCsoFileName = FileSystem::getPath("shader_source/01_sole_feature/texture_feature/05_case_texture_cube_array_rgba8/05_case_texture_cube_array_rgba8_vs.cso");
	std::string vsFileName = FileSystem::getPath("shader_source/01_sole_feature/texture_feature/05_case_texture_cube_array_rgba8/05_case_texture_cube_array_rgba8_vs.hlsl");
	vsCsoFileWss << vsCsoFileName.c_str();
	vsFileWss << vsFileName.c_str();
	//创建顶点着色器
	HR(CreateShaderFromFile(nullptr, vsFileWss.str().c_str(),"VS","vs_5_0",blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf()));
	//创建并绑定顶点布局
	HR(m_pd3dDevice->CreateInputLayout(VertexPosColor::inputLayout, ARRAYSIZE(VertexPosColor::inputLayout), blob->GetBufferPointer(),
		blob->GetBufferSize(), m_pVertexLayout.GetAddressOf()));

	std::string psCsoFileName = FileSystem::getPath("shader_source/01_sole_feature/texture_feature/05_case_texture_cube_array_rgba8/05_case_texture_cube_array_rgba8_ps.cso");
	std::string psFileName = FileSystem::getPath("shader_source/01_sole_feature/texture_feature/05_case_texture_cube_array_rgba8/05_case_texture_cube_array_rgba8_ps.hlsl");
	std::wstringstream psCsoFileWss;
	std::wstringstream psFileWss;
	psCsoFileWss << psCsoFileName.c_str();
	psFileWss << psFileName.c_str();

	//创建像素着色器	
	HR(CreateShaderFromFile(nullptr,psFileWss.str().c_str(), "PS", "ps_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pPixelShader.GetAddressOf()));
	return true;
}

bool CaseApp::initResource()
{
	using vec3 = DirectX::XMFLOAT3;
	using vec4 = DirectX::XMFLOAT4;
	using vec2 = DirectX::XMFLOAT2;
	//顶点数据

	VertexPosColor vertexData[] =
	{
		{vec4(-0.5f,0.5f,-0.5f,1.0f),vec4(1.0f,0.0f,0.0f,1.0f)},//左上 前 0
		{vec4(-0.5f,-0.5f,-0.5f,1.0f),vec4(0.0f,1.0f,0.0f,1.0f)},//左下 前 1
		{vec4(0.5f,-0.5f,-0.5f,1.0f),vec4(0.0f,0.0f,1.0f,1.0f)},//右下 前 2
		{vec4(0.5f,0.5f,-0.5f,1.0f),vec4(1.0f,1.0f,0.0f,1.0f)},//右上  前 3

		{vec4(-0.5f,0.5f,0.5f,1.0f),vec4(1.0f,1.0f,0.0f,1.0f)},//左上 后 4
		{vec4(-0.5f,-0.5f,0.5f,1.0f),vec4(0.0f,1.0f,0.0f,1.0f)},//左下 后 5
		{vec4(0.5f,-0.5f,0.5f,1.0f),vec4(0.0f,0.0f,1.0f,1.0f)},//右下  后 6
		{vec4(0.5f,0.5f,0.5f,1.0f),vec4(0.0f,1.0f,1.0f,1.0f)},//右上  后 7
	};

	VertexInstance instanceData[] =
	{
		{vec3(0.0f,0.0f,0.0f)},
		{vec3(1.5f,0.0f,0.0f)},
		{vec3(-1.5f,0.0f,0.0f)},
	};


	DWORD indexData[] = {
		0,3,2,2,1,0,//正面
		5,4,0,0,1,5,//左面
		4,7,3,3,0,4,//上面
		4,5,6,6,7,4,//后面
		3,7,6,6,2,3,//右面
		2,6,5,5,1,2,//下面
	};
	
	
	//创建顶点数据描述
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(vertexData);
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	
	//新建顶点缓冲
	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData,sizeof(initData));
	initData.pSysMem = vertexData;
	HR(m_pd3dDevice->CreateBuffer(&vbd, &initData, m_pVertexBuffer[0].GetAddressOf()));

	//新建实例缓冲数据
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.ByteWidth = sizeof(instanceData);
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	ZeroMemory(&initData, sizeof(initData));
	initData.pSysMem = instanceData;
	HR(m_pd3dDevice->CreateBuffer(&vbd,&initData, m_pVertexBuffer[1].GetAddressOf()));
	
	//创建索引描述
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(indexData);
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;

	//新建索引缓冲
	initData.pSysMem = indexData;
	HR(m_pd3dDevice->CreateBuffer(&ibd, &initData, m_pIndexBuffer.GetAddressOf()));
	
	//新建常量缓冲
	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.ByteWidth = sizeof(ConstantMat);
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	HR(m_pd3dDevice->CreateBuffer(&cbd, nullptr, m_pConstantBuffer.GetAddressOf()));

	D3D11_TEXTURE2D_DESC tex2dDesc;
	tex2dDesc.Width = 64;
	tex2dDesc.Height = 64;
	tex2dDesc.MipLevels = 1;//使用mipmap
	tex2dDesc.ArraySize = 18;
	tex2dDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tex2dDesc.Usage = D3D11_USAGE_DEFAULT;
	tex2dDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	tex2dDesc.CPUAccessFlags = 0;
	tex2dDesc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
	tex2dDesc.SampleDesc.Count = 1; //msaa采样数
	tex2dDesc.SampleDesc.Quality = 0;//msaa质量等级
	
	unsigned char color [6][4] = {{255,0,0,255},
								  {0,255,0,255},
								  {0,0,255,255},
								  {0,0,0,255},
								  {255,255,0,255},
								  {255,255,255,255},
	};


	int i = 0;
	int j = 0;
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 4096; j++)
		{
			memcpy(&data[i][j][0], &color[i], 4);
		}
	}

	unsigned char data1[4][4] = { {255,0,0,255},
							{0,255,0,255},
							{0,0,255,255},
							{0,0,0,255},};

	unsigned char data2[1][4] = { 255,255,255,255 };
	/*
	D3D11_SUBRESOURCE_DATA texInitData[2];
	texInitData[0].pSysMem = data;
	texInitData[0].SysMemPitch = 16;//当前子资源一行所占的字节数据(2d/3d)使用
	texInitData[0].SysMemSlicePitch = 64;//当前子资源一个切片所占的字节数据（3d)使用

	texInitData[1].pSysMem = data1;
	texInitData[1].SysMemPitch = 8;//当前子资源一行所占的字节数据(2d/3d)使用
	texInitData[1].SysMemSlicePitch = 0;//当前子资源一个切片所占的字节数据（3d)使用
	*/
	
	HR(m_pd3dDevice->CreateTexture2D(&tex2dDesc,nullptr, m_pTexture2D.GetAddressOf()));
	m_pTexture2D->GetDesc(&tex2dDesc);

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 6; j++)
		{
			m_pd3dImmediateContext->UpdateSubresource(m_pTexture2D.Get(),
				D3D10CalcSubresource(0, (D3D11_TEXTURECUBE_FACE_POSITIVE_X + j)+(i*6), tex2dDesc.MipLevels),
				nullptr, &data[j], 256, 1);
		}

	}
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//srvDesc.Texture2D.MipLevels = 1;//使用1mipmap
	//srvDesc.Texture2D.MostDetailedMip = 0;//初始使用1等级的map
	srvDesc.TextureCubeArray.MipLevels = 1;//使用1mipmap
	srvDesc.TextureCubeArray.MostDetailedMip = 0;//初始使用1等级的map
	srvDesc.TextureCubeArray.First2DArrayFace = 0;
	srvDesc.TextureCubeArray.NumCubes = 3;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBEARRAY;

	HR(m_pd3dDevice->CreateShaderResourceView(m_pTexture2D.Get(),&srvDesc,m_pWoodCrate.GetAddressOf()));
	
	//初始化纹理过滤器
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	HR(m_pd3dDevice->CreateSamplerState(&sampDesc, m_pSamplerState.GetAddressOf()));
	

	unsigned int stride[2] = { sizeof(VertexPosColor),sizeof(VertexInstance) };
	unsigned int offset[2] = { 0,0 };
	m_pd3dImmediateContext->IASetVertexBuffers(0,2, m_pVertexBuffer->GetAddressOf(),stride,offset);
	//设置图元类型，设置输入布局
	m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());
	//设置索引缓冲设置
	m_pd3dImmediateContext->IASetIndexBuffer(m_pIndexBuffer.Get(),DXGI_FORMAT_R32_UINT, 0);

	//将着色器绑定到渲染管线
	m_pd3dImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
	m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);
	
	//设置着色器资源视图
	m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pWoodCrate.GetAddressOf());
	//设置过滤器
	m_pd3dImmediateContext->PSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());

	m_pd3dImmediateContext->VSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
	return true;
}


void CaseApp::OnResize()
{
	D3DApp::OnResize();
}

void CaseApp::UpdateScene(float dt)
{

}

void CaseApp::updateMat()
{
	ZeroMemory(&m_constMat, sizeof(m_constMat));
	static float xangle = 0.35f;
	static float yangle = 0.35f;

	xangle += 0.001f;
	yangle += 0.001f;
	m_constMat.modelMat = DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationX(xangle) * DirectX::XMMatrixRotationY(yangle));
	m_constMat.viewMat = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0.0f, 0.0f, -4.0f, 1.0f),
													DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
													DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f)));
	m_constMat.projectMat = DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2, AspectRatio(), 1.0f, 1000.0f));

	D3D11_MAPPED_SUBRESOURCE mapData;
	m_pd3dImmediateContext->Map(m_pConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapData);
	memcpy_s(mapData.pData, sizeof(m_constMat), &m_constMat, sizeof(m_constMat));
	m_pd3dImmediateContext->Unmap(m_pConstantBuffer.Get(), 0);
}

void CaseApp::DrawScene()
{
	assert(m_pd3dImmediateContext);
	assert(m_pSwapChain);
	static float blue[4] = { 0.2f, 0.3f, 0.3f, 0.1f };	// RGBA = (0,0,255,255)
	updateMat();
	m_pd3dImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), blue); 
	m_pd3dImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	//m_pd3dImmediateContext->DrawIndexed(36, 0, 0);
	m_pd3dImmediateContext->DrawIndexedInstanced(36, 3, 0, 0, 0);
	HR(m_pSwapChain->Present(0, 0));
}
