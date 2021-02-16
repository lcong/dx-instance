#ifndef APINSTANCE_H
#define APINSTANCE_H

#include "d3dApp.h"

class ApInstance : public D3DApp
{
public:
	struct VertexPosColor
	{
		DirectX::XMFLOAT4 pos;
		DirectX::XMFLOAT4 color;
		static const D3D11_INPUT_ELEMENT_DESC inputLayout[2];
	};

public:
	ApInstance(HINSTANCE hInstance);
	~ApInstance();

	bool Init();
	void OnResize();
	void DrawScene();

	
private:

	bool InitEffect();
	bool InitResource();
	bool InitOtherVertex();



private:
	ComPtr<ID3D11InputLayout> m_pVertexLayout;	// 顶点输入布局
	ComPtr<ID3D11Buffer> m_pVertexBuffer;		// 顶点缓冲区
	ComPtr<ID3D11VertexShader> m_pVertexShader;	// 顶点着色器
	ComPtr<ID3D11PixelShader> m_pPixelShader;	// 像素着色器
};


#endif