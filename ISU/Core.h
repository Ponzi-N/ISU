#include <Windows.h>
#include <d2d1.h>
#include "InputHandler.h"
#include "Graphics.h"
#include "FPS.h"
#include "CPU.h"
#include "Timing.h"

class pEngine
{
protected:
	//Win32 Varibles
	HWND pHandle;
	HINSTANCE pInstance;
	int pWidth;
	int pHeight;
	char* pTitle;
	//Input Handler apart of Win32 LLHook
	InputHandler* Input;
	GraphicsClass* Graphics;
	FpsClass* Fps;
	CpuClass* Cpu;
	TimerClass* Timer;

	bool InitializeWindow();
	bool InitializeInput();
	bool InitializeD3D();
	bool IntilaizeMonitor();
	bool IntilaizeTimer();
public:
	pEngine(HINSTANCE hInstance);
	virtual ~pEngine();

	int RunEngine();
	virtual bool InitializeEngine();
	virtual void Tick(float DeltaTime) = 0;
	virtual void RenderEngine() = 0;

	LRESULT MsgHandler(HWND hwnd, UINT Msg, WPARAM WindowParameters, LPARAM lParam);
};