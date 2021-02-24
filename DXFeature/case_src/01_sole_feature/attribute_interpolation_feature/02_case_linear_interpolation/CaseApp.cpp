#include "CaseApp.h"
#include "d3dUtil.h"
#include "DXTrace.h"
#include "filesystem.h"
#include <sstream>

const D3D11_INPUT_ELEMENT_DESC CaseApp::VertexPosColor::inputLayout[2] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

CaseApp::CaseApp(HINSTANCE hInstance)
	: D3DApp(hInstance)
{
	m_MainWndCaption = L"02_case_linear_interpolation";
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
	return true;
}

bool CaseApp::initEffect()
{
	ComPtr<ID3DBlob> blob;
	std::wstringstream vsCsoFileWss;
	std::wstringstream vsFileWss;
	std::string vsCsoFileName = FileSystem::getPath("shader_source/01_sole_feature/attribute_interpolation_feature/02_case_linear_interpolation/02_case_linear_interpolation_vs.cso");
	std::string vsFileName = FileSystem::getPath("shader_source/01_sole_feature/attribute_interpolation_feature/02_case_linear_interpolation/02_case_linear_interpolation_vs.hlsl");
	vsCsoFileWss << vsCsoFileName.c_str();
	vsFileWss << vsFileName.c_str();
	//创建顶点着色器
	HR(CreateShaderFromFile(vsCsoFileWss.str().c_str(), vsFileWss.str().c_str(),"VS","vs_5_0",blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf()));
	//创建并绑定顶点布局
	HR(m_pd3dDevice->CreateInputLayout(VertexPosColor::inputLayout, ARRAYSIZE(VertexPosColor::inputLayout), blob->GetBufferPointer(),
		blob->GetBufferSize(), m_pVertexLayout.GetAddressOf()));

	std::string psCsoFileName = FileSystem::getPath("shader_source/01_sole_feature/attribute_interpolation_feature/02_case_linear_interpolation/02_case_linear_interpolation_ps.cso");
	std::string psFileName = FileSystem::getPath("shader_source/01_sole_feature/attribute_interpolation_feature/02_case_linear_interpolation/02_case_linear_interpolation_ps.hlsl");
	std::wstringstream psCsoFileWss;
	std::wstringstream psFileWss;
	psCsoFileWss << psCsoFileName.c_str();
	psFileWss << psFileName.c_str();

	//创建像素着色器	
	HR(CreateShaderFromFile(psCsoFileWss.str().c_str(),psFileWss.str().c_str(), "PS", "ps_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pPixelShader.GetAddressOf()));
	return true;
}

bool CaseApp::initResource()
{
	using vec3 = DirectX::XMFLOAT3;
	using vec4 = DirectX::XMFLOAT4;
	//顶点数据
	VertexPosColor vertexData[] =
	{
		{vec4(0.0f,0.5f,0.2f,0.5f),vec4(1.0f,0.0f,0.0f,1.0f)},
		{vec4(0.5f,-0.5f,0.2f,0.7f),vec4(0.0f,1.0f,0.0f,1.0f)},
		{vec4(-0.5f,-0.5f,0.2f,0.9f),vec4(0.0f,0.0f,1.0f,1.0f)},
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
	
	unsigned int stride = sizeof(VertexPosColor);
	unsigned int offset = 0;
	m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
	//设置图元类型，设置输入布局
	m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());

	//将着色器绑定到渲染管线
	m_pd3dImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
	m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);
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

	m_pd3dImmediateContext->Draw(3,0);
	HR(m_pSwapChain->Present(0, 0));
}
