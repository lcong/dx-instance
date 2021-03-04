#include "CaseApp.h"
#include "d3dUtil.h"
#include "DXTrace.h"
#include "filesystem.h"
#include <sstream>

const D3D11_INPUT_ELEMENT_DESC CaseApp::VertexPosColor::inputLayout[1] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

const D3D11_SO_DECLARATION_ENTRY posLayout[1] = {
	{ 0,"SV_POSITION", 0, 0, 4, 0 },
};


CaseApp::CaseApp(HINSTANCE hInstance)
	: D3DApp(hInstance)
{
	m_MainWndCaption = L"02_case_stream_output_with_patch_list";
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

	/*
	std::wstringstream vsFileWss;
	std::string vsFileName = FileSystem::getPath("shader_source/01_sole_feature/stream_output_feature/02_case_stream_output_with_patch_list/02_case_stream_output_with_patch_list_vs.hlsl");
	vsFileWss << vsFileName.c_str();
	//创建 so 顶点着色器
	HR(CreateShaderFromFile(nullptr, vsFileWss.str().c_str(),"VS","vs_5_0",blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf()));
	*/
	//创建draw 顶点着色器
	std::string drawVsFileName = FileSystem::getPath("shader_source/01_sole_feature/stream_output_feature/02_case_stream_output_with_patch_list/02_case_stream_output_with_patch_list_vs.hlsl");
	std::wstringstream vsDrwaWss;
	vsDrwaWss << drawVsFileName.c_str();
	HR(CreateShaderFromFile(nullptr, vsDrwaWss.str().c_str(), "VS", "vs_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pDrawVertexShader.GetAddressOf()));

	//使用vertexShader创建不带gs 的流输出几何着色器
	HR(m_pd3dDevice->CreateGeometryShaderWithStreamOutput(blob->GetBufferPointer(), blob->GetBufferSize(),
		posLayout, ARRAYSIZE(posLayout), nullptr, 0, D3D11_SO_NO_RASTERIZED_STREAM, nullptr, m_pGeometryShader.GetAddressOf()));


	//创建并绑定顶点布局
	HR(m_pd3dDevice->CreateInputLayout(VertexPosColor::inputLayout, ARRAYSIZE(VertexPosColor::inputLayout), blob->GetBufferPointer(),
		blob->GetBufferSize(), m_pVertexLayout.GetAddressOf()));

	/*
	//创建外壳着色器
	std::wstringstream hsFileWss;
	std::string hsFileName = FileSystem::getPath("shader_source/01_sole_feature/stream_output_feature/02_case_stream_output_with_patch_list/02_case_stream_output_with_patch_list_hs.hlsl");
	hsFileWss << hsFileName.c_str();
	HR(CreateShaderFromFile(nullptr, hsFileWss.str().c_str(), "HS", "hs_5_0",blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreateHullShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pHullShader.GetAddressOf()));

	//创建域着色器
	std::wstringstream dsFileWss;
	std::string dsFileName = FileSystem::getPath("shader_source/01_sole_feature/stream_output_feature/02_case_stream_output_with_patch_list/02_case_stream_output_with_patch_list_ds.hlsl");
	dsFileWss << dsFileName.c_str();
	HR(CreateShaderFromFile(nullptr, dsFileWss.str().c_str(), "DS", "ds_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreateDomainShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pDomainShader.GetAddressOf()));
	*/
	//创建像素着色器	
	std::string psFileName = FileSystem::getPath("shader_source/01_sole_feature/stream_output_feature/02_case_stream_output_with_patch_list/02_case_stream_output_with_patch_list_ps.hlsl");
	std::wstringstream psFileWss;
	psFileWss << psFileName.c_str();
	HR(CreateShaderFromFile(nullptr,psFileWss.str().c_str(), "PS", "ps_5_0", blob.ReleaseAndGetAddressOf()));
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
		{vec4(-0.5f,0.5f,0.2f,1.0f)},
		{vec4(-0.7f,-0.5f,0.2f,1.0f)},
		{vec4(-0.3f,-0.5f,0.2f,1.0f)},

		{vec4(0.5f,0.5f,0.2f,1.0f)},
		{vec4(0.3f,-0.5f,0.2f,1.0f)},
		{vec4(0.7f,-0.5f,0.2f,1.0f)},

		{vec4(-0.5f,0.0f,0.2f,1.0f)},
		{vec4(0.5f,0.0f,0.2f,1.0f)},

	};
	//创建顶点数据描述
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.ByteWidth = sizeof(vertexData);
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER | D3D11_BIND_STREAM_OUTPUT;
	vbd.CPUAccessFlags = 0;
	
	//新建顶点缓冲
	D3D11_SUBRESOURCE_DATA initData;
	ZeroMemory(&initData,sizeof(initData));
	initData.pSysMem = vertexData;
	HR(m_pd3dDevice->CreateBuffer(&vbd, &initData, m_pVertexBuffer.GetAddressOf()));

	vbd.ByteWidth = sizeof(vertexData);
	HR(m_pd3dDevice->CreateBuffer(&vbd, nullptr, m_pVertexBufferOut.GetAddressOf()));

	unsigned int stride = sizeof(VertexPosColor);
	unsigned int offset = 0;
	
	m_pd3dImmediateContext->SOSetTargets(1, m_pVertexBufferOut.GetAddressOf(), 0);

	m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);

	//设置图元类型，设置输入布局
	m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
	m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());

	//将着色器绑定到渲染管线
	m_pd3dImmediateContext->VSSetShader(m_pDrawVertexShader.Get(), nullptr, 0);
	//m_pd3dImmediateContext->HSSetShader(m_pHullShader.Get(), nullptr, 0);
	//m_pd3dImmediateContext->DSSetShader(m_pDomainShader.Get(), nullptr, 0);
	m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);
	m_pd3dImmediateContext->GSSetShader(m_pGeometryShader.Get(), nullptr, 0);

	D3D11_QUERY_DESC qDesc;

	qDesc.MiscFlags = 0;
	qDesc.Query = D3D11_QUERY_SO_STATISTICS;
	HR(m_pd3dDevice->CreateQuery(&qDesc, m_pQuery.GetAddressOf()));

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
	
	D3D11_QUERY_DATA_SO_STATISTICS dataSoStatistics;
	
	static float blue[4] = { 0.2f, 0.3f, 0.3f, 0.1f };	

	m_pd3dImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), blue);
	//m_pd3dImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	
	m_pd3dImmediateContext->Begin(m_pQuery.Get());

	m_pd3dImmediateContext->Draw(8,0);

	m_pd3dImmediateContext->End(m_pQuery.Get());

	while (S_OK != m_pd3dImmediateContext->GetData(m_pQuery.Get(), &dataSoStatistics, sizeof(dataSoStatistics), 0))
	{
		Sleep(1000);
	}

	HR(m_pSwapChain->Present(0, 0));
	unsigned int stride = sizeof(VertexPosColor);
	unsigned int offset = 0;

	m_pd3dImmediateContext->SOSetTargets(0,nullptr, 0);
	m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBufferOut.GetAddressOf(), &stride, &offset);
	m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	m_pd3dImmediateContext->GSSetShader(nullptr, nullptr, 0);
	//m_pd3dImmediateContext->HSSetShader(nullptr, nullptr, 0);
	//m_pd3dImmediateContext->DSSetShader(nullptr, nullptr, 0);
	m_pd3dImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), blue);
	m_pd3dImmediateContext->Draw(8,0);

	HR(m_pSwapChain->Present(0, 0));
}
