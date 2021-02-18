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
};


#endif