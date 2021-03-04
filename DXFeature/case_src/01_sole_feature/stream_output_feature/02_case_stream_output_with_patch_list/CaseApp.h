#ifndef CASEAPP_H
#define CASEAPP_H
#include "d3dApp.h"
class CaseApp : public D3DApp
{
public:
	CaseApp(HINSTANCE hInstance);
	~CaseApp();
	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene();
public:
	struct VertexPosColor
	{
		DirectX::XMFLOAT4 pos;
		static const D3D11_INPUT_ELEMENT_DESC inputLayout[1];
	};

private:
	bool initResource();
	bool initEffect();

private:
	ComPtr<ID3D11InputLayout> m_pVertexLayout;	// 顶点输入布局
	ComPtr<ID3D11Buffer> m_pVertexBuffer;		// 顶点缓冲区
	ComPtr<ID3D11VertexShader> m_pVertexShader;	// stream_out 顶点着色器
	ComPtr<ID3D11VertexShader> m_pDrawVertexShader; //draw 顶点着色器
	ComPtr<ID3D11PixelShader> m_pPixelShader;	// 像素着色器
	ComPtr<ID3D11GeometryShader> m_pGeometryShader; //几何着色器
	ComPtr<ID3D11HullShader> m_pHullShader;  //外壳着色器
	ComPtr<ID3D11DomainShader> m_pDomainShader; //域着色器
	ComPtr<ID3D11Buffer> m_pVertexBufferOut; //流输出缓冲区
	ComPtr<ID3D11Query> m_pQuery;
};


#endif