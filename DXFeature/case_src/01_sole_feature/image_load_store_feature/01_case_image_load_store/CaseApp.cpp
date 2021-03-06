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
	{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,32,D3D11_INPUT_PER_VERTEX_DATA,0}
};

CaseApp::CaseApp(HINSTANCE hInstance)
	: D3DApp(hInstance)
{
	m_MainWndCaption = L"01_case_image_load_store";
	m_EnableDebug = false;
	m_setSize = 8;
}

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
	std::string vsCsoFileName = FileSystem::getPath("shader_source/01_sole_feature/image_load_store_feature/01_case_image_load_store/01_case_image_load_store_vs.cso");
	std::string vsFileName = FileSystem::getPath("shader_source/01_sole_feature/image_load_store_feature/01_case_image_load_store/01_case_image_load_store_vs.hlsl");
	vsCsoFileWss << vsCsoFileName.c_str();
	vsFileWss << vsFileName.c_str();
	//创建顶点着色器
	HR(CreateShaderFromFile(vsCsoFileWss.str().c_str(), vsFileWss.str().c_str(),"VS","vs_5_0",blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf()));
	//创建并绑定顶点布局
	HR(m_pd3dDevice->CreateInputLayout(VertexPosColor::inputLayout, ARRAYSIZE(VertexPosColor::inputLayout), blob->GetBufferPointer(),
		blob->GetBufferSize(), m_pVertexLayout.GetAddressOf()));

	std::string psCsoFileName = FileSystem::getPath("shader_source/01_sole_feature/image_load_store_feature/01_case_image_load_store/01_case_image_load_store_ps.cso");
	std::string psFileName = FileSystem::getPath("shader_source/01_sole_feature/image_load_store_feature/01_case_image_load_store/01_case_image_load_store_ps.hlsl");
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
		{vec4(-0.5f,0.5f,0.2f,1.0f),vec4(1.0f,0.0f,0.0f,1.0f),vec2(0,0)},
		{vec4(-0.5f,-0.5f,0.2f,1.0f),vec4(1.0f,0.0f,0.0f,1.0f),vec2(0.0f,1.0f)},
		{vec4(0.5f,-0.5f,0.2f,1.0f),vec4(1.0f,0.0f,0.0f,1.0f),vec2(1.0f,1.0f)},
		{vec4(0.5f,0.5f,0.2f,1.0f),vec4(1.0f,0.0f,0.0f,1.0f),vec2(1.0f,0)},
	};
	DWORD indices[] = {0,2,1,0,3,2};
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
	HR(m_pd3dDevice->CreateBuffer(&vbd, &initData, m_pVertexBuffer.GetAddressOf()));

	//创建索引描述
	D3D11_BUFFER_DESC ibd;
	ZeroMemory(&ibd, sizeof(ibd));
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(indices);
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;

	//新建索引缓冲
	initData.pSysMem = indices;
	HR(m_pd3dDevice->CreateBuffer(&ibd, &initData, m_pIndexBuffer.GetAddressOf()));
	
	
	//初始化木箱纹理
	//std::string pictureFileName = FileSystem::getPath("resources/WoodCrate.dds");
	//std::wstringstream ws;
	//ws << pictureFileName.c_str();
	//HR(DirectX::CreateDDSTextureFromFile(m_pd3dDevice.Get(), ws.str().c_str(), nullptr, m_pWoodCrate.GetAddressOf()));
	//使用内存数据初始化纹理
	D3D11_TEXTURE2D_DESC tex2dDesc;
	tex2dDesc.Width = 4;
	tex2dDesc.Height = 4;
	tex2dDesc.MipLevels = 1;//使用mipmap
	tex2dDesc.ArraySize = 1;
	tex2dDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tex2dDesc.Usage = D3D11_USAGE_DEFAULT;
	tex2dDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	tex2dDesc.CPUAccessFlags = 0;
	tex2dDesc.MiscFlags = 0;
	tex2dDesc.SampleDesc.Count = 1; //msaa采样数
	tex2dDesc.SampleDesc.Quality = 0;//msaa质量等级
	
	unsigned char data[16][4] = { {255,0,0,255},{0,255,0,255},{0,0,255,255},{0,0,0,255},
								{0,255,0,255},{0,0,255,255},{0,0,0,255},{255,0,0,255},
								{0,0,255,255},{0,0,0,255},{255,0,0,255},{0,255,0,255},
								{0,0,0,255},{255,0,0,255}, {0,255,0,255}, {0,0,255,255}};

	D3D11_SUBRESOURCE_DATA texInitData;
	texInitData.pSysMem = data;
	texInitData.SysMemPitch = 16;//当前子资源一行所占的字节数据(2d/3d)使用
	texInitData.SysMemSlicePitch = 64;//当前子资源一个切片所占的字节数据（3d)使用

	HR(m_pd3dDevice->CreateTexture2D(&tex2dDesc,&texInitData, m_pTextureInput.GetAddressOf()));

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.Texture2D.MipLevels = 1;//使用1mipmap
	srvDesc.Texture2D.MostDetailedMip = 0;//初始使用1等级的map
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	HR(m_pd3dDevice->CreateShaderResourceView(m_pTextureInput.Get(),&srvDesc,m_pShaderResource.GetAddressOf()));

	D3D11_TEXTURE2D_DESC uavTexDesc;
	uavTexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	uavTexDesc.ArraySize = 1;
	uavTexDesc.MipLevels = 1;
	uavTexDesc.Usage = D3D11_USAGE_DEFAULT;
	uavTexDesc.SampleDesc.Count = 1;
	uavTexDesc.SampleDesc.Quality = 0;
	uavTexDesc.CPUAccessFlags = 0;
	uavTexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
	uavTexDesc.MiscFlags = 0;
	uavTexDesc.Width = 4;
	uavTexDesc.Height = 4;
	HR(m_pd3dDevice->CreateTexture2D(&uavTexDesc, nullptr, m_pTextureOutput.GetAddressOf()));
	D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
	uavDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	uavDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
	uavDesc.Texture2D.MipSlice = 0;
	HR(m_pd3dDevice->CreateUnorderedAccessView(m_pTextureOutput.Get(), &uavDesc,m_pUnorderedAccess.GetAddressOf()));

	unsigned int stride = sizeof(VertexPosColor);
	unsigned int offset = 0;
	m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
	//设置图元类型，设置输入布局
	m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());
	//设置索引缓冲设置
	m_pd3dImmediateContext->IASetIndexBuffer(m_pIndexBuffer.Get(),DXGI_FORMAT_R32_UINT, 0);

	//将着色器绑定到渲染管线
	m_pd3dImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
	m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);
	
	//设置着色器资源视图
	m_pd3dImmediateContext->PSSetShaderResources(0, 1, m_pShaderResource.GetAddressOf());
	//设置uav
	m_pd3dImmediateContext->OMSetRenderTargetsAndUnorderedAccessViews(1, m_pRenderTargetView.GetAddressOf(), nullptr, 1,
																		1,m_pUnorderedAccess.GetAddressOf(), nullptr);

	//设置过滤器
	//m_pd3dImmediateContext->PSSetSamplers(0, 1, m_pSamplerState.GetAddressOf());

	return true;
}


void CaseApp::OnResize()
{
	D3DApp::OnResize();
}

void CaseApp::UpdateScene(float dt)
{

}

void CaseApp::DrawScene()
{
	assert(m_pd3dImmediateContext);
	assert(m_pSwapChain);
	static float blue[4] = { 0.2f, 0.3f, 0.3f, 0.1f };	// RGBA = (0,0,255,255)
	m_pd3dImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), blue); 
	//m_pd3dImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_pd3dImmediateContext->DrawIndexed(6, 0, 0);
	

	HR(m_pSwapChain->Present(0, 0));
}
