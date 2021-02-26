#include "ApInstance.h"
#include "d3dUtil.h"
#include "DXTrace.h"
#include <sstream>
#include "filesystem.h"
#include <sstream>

using namespace DirectX;

const D3D11_INPUT_ELEMENT_DESC ApInstance::VertexPosColor::inputLayout[2] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * sizeof(float), D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

ApInstance::ApInstance(HINSTANCE hInstance)
	: D3DApp(hInstance)
{
	m_MainWndCaption = L"01_case_stencil_notequal";
	m_EnableDebug = false;
	m_EnableDepthTest = true;
}

ApInstance::~ApInstance()
{
}

void ApInstance::UpdateScene(float dt)
{

}

bool ApInstance::Init()
{
	if (!D3DApp::Init())
		return false;

	if (!InitEffect())
		return false;

	//绘制模板三角形
	InitResource();

	return true;
}

void ApInstance::OnResize()
{
	D3DApp::OnResize();
}

void ApInstance::DrawScene()    
{
	assert(m_pd3dImmediateContext);
	assert(m_pSwapChain);
	UINT stride = sizeof(VertexPosColor);	// 跨越字节数
	UINT offset = 0;

	static float black[4] = { 0.0f, 0.0f, 0.0f, 1.0f };	// RGBA = (0,0,0,255)
	m_pd3dImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), black);
	m_pd3dImmediateContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	    
	D3D11_DEPTH_STENCIL_DESC dsDesc;

	//禁止使用深度测试
	dsDesc.DepthEnable = false;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	//开启模板测试
	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	
	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// 对于背面的几何体我们是不进行渲染的，所以这里的设置无关紧要  要加上，否则报错
	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	HR(m_pd3dDevice.Get()->CreateDepthStencilState(&dsDesc, m_pWriteStencil.GetAddressOf()));

	//m_pd3dImmediateContext->RSSetState(nullptr);

	//将模板缓冲的值设置为1
	m_pd3dImmediateContext->OMSetDepthStencilState(m_pWriteStencil.Get(), 1);

	m_pd3dImmediateContext->Draw(3, 0);
	
	//禁止模板缓冲值写入
	dsDesc.StencilEnable = true;
	dsDesc.StencilWriteMask = 0x00;
	//只有模板缓冲中不为1的部分才会通过模板测试
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_NOT_EQUAL;

	m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer2.GetAddressOf(), &stride, &offset);
	HR(m_pd3dDevice.Get()->CreateDepthStencilState(&dsDesc,m_pWriteStencil.ReleaseAndGetAddressOf()));

	//m_pd3dImmediateContext->RSSetState(nullptr);
	m_pd3dImmediateContext->OMSetDepthStencilState(m_pWriteStencil.Get(), 1);

	m_pd3dImmediateContext->Draw(3, 0);
	HR(m_pSwapChain->Present(0, 0));
}

bool ApInstance::InitEffect()
{
	ComPtr<ID3DBlob> blob;
	std::wstringstream vsNameWss;
	std::string vsFileName = FileSystem::getPath("shader_source/01_sole_feature/stencil_feature/01_case_stencil_notequal/01_case_stencil_notequal_VS.hlsl");
	vsNameWss << vsFileName.c_str();
	// 创建顶点着色器
	HR(CreateShaderFromFile(nullptr,vsNameWss.str().c_str(), "VS", "vs_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pVertexShader.GetAddressOf()));
	// 创建并绑定顶点布局
	HR(m_pd3dDevice->CreateInputLayout(VertexPosColor::inputLayout, ARRAYSIZE(VertexPosColor::inputLayout),
		blob->GetBufferPointer(), blob->GetBufferSize(), m_pVertexLayout.GetAddressOf()));

	std::wstringstream psNameWss;
	std::string psFileName = FileSystem::getPath("shader_source/01_sole_feature/stencil_feature/01_case_stencil_notequal/01_case_stencil_notequal_PS.hlsl");
	psNameWss << psFileName.c_str();
	// 创建像素着色器
	HR(CreateShaderFromFile(nullptr, psNameWss.str().c_str(), "PS", "ps_5_0", blob.ReleaseAndGetAddressOf()));
	HR(m_pd3dDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_pPixelShader.GetAddressOf()));

	return true;
}

bool ApInstance::InitResource()
{
	// 设置第一个三角形顶点
	VertexPosColor vertices[] =
	{
		{ XMFLOAT4(-0.5f, 0.5f, 0.5f,1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT4(0.5f, 0.5f,  0.5f,1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT4(0.0f, -0.5f, 0.5f,1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
	};

	VertexPosColor vertices2[] =
	{
		{ XMFLOAT4(-0.5f, -0.5f, 0.4f,1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT4(0.0f,  0.5f,  0.4f,1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT4(0.5f, -0.5f, 0.4f,1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) }
	};

	// 设置顶点缓冲区描述
	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof vertices;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	// 新建顶点缓冲区
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;
	HR(m_pd3dDevice->CreateBuffer(&vbd, &InitData, m_pVertexBuffer.GetAddressOf()));
	
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices2;
	HR(m_pd3dDevice->CreateBuffer(&vbd, &InitData, m_pVertexBuffer2.GetAddressOf()));

	// ******************
	// 给渲染管线各个阶段绑定好所需资源
	//

	// 输入装配阶段的顶点缓冲区设置
	UINT stride = sizeof(VertexPosColor);	// 跨越字节数
	UINT offset = 0;						// 起始偏移量

	m_pd3dImmediateContext->IASetVertexBuffers(0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);
	// 设置图元类型，设定输入布局
	m_pd3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pd3dImmediateContext->IASetInputLayout(m_pVertexLayout.Get());
	// 将着色器绑定到渲染管线
	m_pd3dImmediateContext->VSSetShader(m_pVertexShader.Get(), nullptr, 0);
	m_pd3dImmediateContext->PSSetShader(m_pPixelShader.Get(), nullptr, 0);

	return true;
}
