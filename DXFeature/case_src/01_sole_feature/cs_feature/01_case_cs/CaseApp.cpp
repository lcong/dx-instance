#include "CaseApp.h"
#include "d3dUtil.h"
#include "DXTrace.h"
#include "filesystem.h"
#include <sstream>
#include "DDSTextureLoader.h"
#include "WICTextureLoader.h"
#include "ScreenGrab.h"

const D3D11_INPUT_ELEMENT_DESC CaseApp::VertexPosColor::inputLayout[2] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

CaseApp::CaseApp(HINSTANCE hInstance)
	: D3DApp(hInstance)
{
	m_MainWndCaption = L"01_case_cs";
	m_EnableDebug = false;
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
	Compute();
	return true;
}

bool CaseApp::initEffect()
{
	/*
	ComPtr<ID3DBlob> blob;
	std::wstringstream vsCsoFileWss;
	std::wstringstream vsFileWss;
	std::string vsCsoFileName = FileSystem::getPath("shader_source/01_sole_feature/cs_feature/01_case_cs/001_case_cs_vs.cso");
	std::string vsFileName = FileSystem::getPath("shader_source/01_sole_feature/cs_feature/01_case_cs/01_case_cs_vs.hlsl");
	vsCsoFileWss << vsCsoFileName.c_str();
	vsFileWss << vsFileName.c_str();
	//创建顶点着色器
	HR(CreateShaderFromFile(vsCsoFileWss.str().c_str(), vsFileWss.str().c_str(),"VS","vs_5_0",blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf()));
	//创建并绑定顶点布局
	HR(m_pd3dDevice->CreateInputLayout(VertexPosColor::inputLayout, ARRAYSIZE(VertexPosColor::inputLayout), blob->GetBufferPointer(),
		blob->GetBufferSize(), m_pVertexLayout.GetAddressOf()));

	std::string psCsoFileName = FileSystem::getPath("shader_source/01_sole_feature/cs_feature/01_case_cs/01_case_cs_ps.cso");
	std::string psFileName = FileSystem::getPath("shader_source/01_sole_feature/cs_feature/01_case_cs/01_case_cs_ps.hlsl");
	std::wstringstream psCsoFileWss;
	std::wstringstream psFileWss;
	psCsoFileWss << psCsoFileName.c_str();
	psFileWss << psFileName.c_str();

	//创建像素着色器	
	HR(CreateShaderFromFile(psCsoFileWss.str().c_str(),psFileWss.str().c_str(), "PS", "ps_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pPixelShader.GetAddressOf()));
	*/
	return true;
}

bool CaseApp::initResource()
{
	/*
	using vec3 = DirectX::XMFLOAT3;
	using vec4 = DirectX::XMFLOAT4;
	//顶点数据
	VertexPosColor vertexData[] =
	{
		{vec4(0.0f,0.5f,0.2f,1.0f),vec4(1.0f,0.0f,0.0f,1.0f)},
		{vec4(0.5f,-0.5f,0.2f,1.0f),vec4(1.0f,0.0f,0.0f,1.0f)},
		{vec4(-0.5f,-0.5f,0.2f,1.0f),vec4(1.0f,0.0f,0.0f,1.0f)},
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
	HR(m_pd3dDevice->CreateBuffer(&vbd, &initData, m_pVertexBuffer.GetAddressOf()));
	*/

	//创建纹理数据资源视图
	/*
	std::string woodPicturePath = FileSystem::getPath("resources/WoodCrate.dds");
	std::wstringstream wss;
	wss << woodPicturePath.c_str();
	HR(DirectX::CreateDDSTextureFromFile(m_pd3dDevice.Get(), wss.str().c_str(),nullptr,m_pTextureInput.GetAddressOf()));
	*/
	D3D11_TEXTURE2D_DESC inputTexDesc;
	inputTexDesc.Width = 4;
	inputTexDesc.Height = 4;
	inputTexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	inputTexDesc.ArraySize = 1;
	inputTexDesc.MipLevels = 1;
	inputTexDesc.Usage = D3D11_USAGE_DEFAULT;
	inputTexDesc.SampleDesc.Count = 1;
	inputTexDesc.SampleDesc.Quality = 0;
	inputTexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	inputTexDesc.CPUAccessFlags = 0;
	inputTexDesc.MiscFlags = 0;

	unsigned char data[16][4] = { {255,0,0,255},{255,0,0,255},{255,0,0,255},{255,0,0,255},
							{0,255,0,255},{0,255,0,255},{0,255,0,255},{0,255,0,255},
							{0,0,255,255},{0,0,255,255},{0,0,255,255},{0,0,255,255},
							{0,0,0,255},{0,0,0,255}, {0,0,0,255}, {0,0,0,255} };
	D3D11_SUBRESOURCE_DATA srvInitData;
	srvInitData.pSysMem = data;
	srvInitData.SysMemPitch = 16;
	srvInitData.SysMemSlicePitch = 64;
	HR(m_pd3dDevice->CreateTexture2D(&inputTexDesc, &srvInitData,m_pTexture2D.GetAddressOf()));

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;
	HR(m_pd3dDevice->CreateShaderResourceView(m_pTexture2D.Get(), &srvDesc, m_pTextureInput.GetAddressOf()));
	
	
	//创建用于uav的纹理
	D3D11_TEXTURE2D_DESC texDesc;
	texDesc.Width = 4;
	texDesc.Height = 4;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	HR(m_pd3dDevice->CreateTexture2D(&texDesc, nullptr, m_pTextureOutput.GetAddressOf()));

	//创建unorderAccessView
	D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
	uavDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	uavDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
	uavDesc.Texture2D.MipSlice = 0;

	HR(m_pd3dDevice->CreateUnorderedAccessView(m_pTextureOutput.Get(), &uavDesc, m_pTextureOut_UAV.GetAddressOf()));

	//创建cs shader
	ComPtr<ID3DBlob> csBlob;
	std::string csShaderPath = FileSystem::getPath("shader_source/01_sole_feature/cs_feature/01_case_cs/01_case_cs_cs.hlsl");
	std::wstringstream csWss;
	csWss << csShaderPath.c_str();
	HR(CreateShaderFromFile(nullptr, csWss.str().c_str(), "CS", "cs_5_0", csBlob.GetAddressOf()));
	HR(m_pd3dDevice->CreateComputeShader(csBlob->GetBufferPointer(), csBlob->GetBufferSize(), nullptr,m_pComputerShader.GetAddressOf()));

	/*
	unsigned int stride = sizeof(VertexPosColor);
	unsigned int offset = 0;
	m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
	//设置图元类型，设置输入布局
	m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());

	//将着色器绑定到渲染管线
	m_pd3dImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
	m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);
	*/
	return true;
}


void CaseApp::Compute()
{
	assert(m_pd3dImmediateContext);
	m_pd3dImmediateContext->CSSetShaderResources(0,1,m_pTextureInput.GetAddressOf());
	m_pd3dImmediateContext->CSSetShader(m_pComputerShader.Get(), nullptr, 0);
	m_pd3dImmediateContext->CSSetUnorderedAccessViews(0, 1, m_pTextureOut_UAV.GetAddressOf(), nullptr);
	m_pd3dImmediateContext->Dispatch(1,1, 1);
	//HR(DirectX::SaveDDSTextureToFile(m_pd3dImmediateContext.Get(), m_pTextureOutput.Get(),L"D:woodCreate.dds"));
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
	/*
	assert(m_pd3dImmediateContext);
	assert(m_pSwapChain);
	static float blue[4] = { 0.2f, 0.3f, 0.3f, 0.1f };	// RGBA = (0,0,255,255)
	m_pd3dImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), blue);
	//m_pd3dImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	m_pd3dImmediateContext->Draw(3,0);
	*/
	HR(m_pSwapChain->Present(0, 0));
}
