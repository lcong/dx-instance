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
	void Compute();
public:
	struct VertexPosColor
	{
		DirectX::XMFLOAT4 pos;
		DirectX::XMFLOAT4 color;
		static const D3D11_INPUT_ELEMENT_DESC inputLayout[2];
	};

private:
	bool initResource();
	bool initEffect();

private:
	ComPtr<ID3D11InputLayout> m_pVertexLayout;	// 顶点输入布局
	ComPtr<ID3D11Buffer> m_pVertexBuffer;		// 顶点缓冲区
	ComPtr<ID3D11VertexShader> m_pVertexShader;	// 顶点着色器
	ComPtr<ID3D11PixelShader> m_pPixelShader;	// 像素着色器
	ComPtr<ID3D11ComputeShader> m_pComputerShader;
	ComPtr<ID3D11Texture2D> m_pTexture2D;
	ComPtr<ID3D11ShaderResourceView> m_pTextureInput;
	ComPtr<ID3D11Texture2D> m_pTextureOutput;
	ComPtr<ID3D11UnorderedAccessView> m_pTextureOut_UAV;

};


#endif