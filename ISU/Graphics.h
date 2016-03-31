const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = false;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

#include "DirectX.h"
#include "CameraHandler.h"
#include "TextHandler.h"


class pGraphics {
public:
	pGraphics();
	pGraphics(const pGraphics&);
	~pGraphics();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(int, int, float);
	bool Render();

private:
	D3DClass* pD3D;
	pCamera* Camera;
	TextClass* pText;
};