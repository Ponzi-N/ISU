#include "Core.h"

/*
We need to make an empty namespace to point our message handler gobally so we can access it through the project.
*/
namespace
{
	pEngine* Engine;
}

LRESULT CALLBACK GameHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return Engine->MsgHandler(hwnd, msg, wParam, lParam);
}

pEngine::pEngine(HINSTANCE hInstance)
{
	pInstance = hInstance;
	pHandle = NULL;
	pWidth = 1920;
	pHeight = 1080;
	pTitle = "The Great Escape!";
	Engine = this;
}

pEngine::~pEngine()
{
	//Release from Memory
}

int pEngine::RunEngine()
{
	MSG msg = {0};
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Tick(0.0f);
		RenderEngine();
	}
	return (int)msg.wParam;
}

bool pEngine::InitializeEngine()
{
	if (!InitializeWindow())
		return false;

	if (!InitializeInput())
		return false;

	if (!InitializeD3D())
		return false;

	if (!IntilaizeMonitor())
		return false;

	if (!IntilaizeTimer())
		return false;

	return true;
}
bool pEngine::IntilaizeTimer()
{
	bool Result;
	Timer = new TimerClass;
	if (!Timer)
	{
		return false;
	}
	Result = Timer->Initialize();

	if (!Result)
	{
		MessageBox(pHandle, "Could not initialize the Timer object.", "Error", MB_OK);
		return false;
	}
}
bool pEngine::IntilaizeMonitor()
{
	Fps = new FpsClass;
	if (!Fps)
	{
		MessageBox(pHandle, "Could not initialize the FPS class.", "Error", MB_OK);
		return false;
	}
	Fps->Initialize();

	Cpu = new CpuClass;
	if (!Cpu)
	{
		MessageBox(pHandle, "Could not initialize the FPS class.", "Error", MB_OK);
		return false;
	}
	Cpu->Initialize();
	return true;
}
bool pEngine::InitializeInput()
{
	bool result;
	Input = new InputHandler;
	if (!Input)
	{
		MessageBox(pHandle, "Could not initialize the input class.", "Error", MB_OK);
		return false;
	}

	result = Input->Initialize(pInstance, pHandle, pHeight, pWidth);
	if (!result)
	{
		MessageBox(pHandle, "Could not initialize the input object.", "Error", MB_OK);
		return false;
	}
}
bool pEngine::InitializeD3D()
{
	// Create the graphics object.  This object will handle rendering all the graphics for this application.
	Graphics = new GraphicsClass;
	if (!Graphics)
	{
		return false;
	}
	return Graphics->Initialize(pWidth, pHeight, pHandle);
}

bool pEngine::InitializeWindow()
{
	//Create the window class for our game
	WNDCLASSEX WindowClass;
	DEVMODE ScreenSettings;
	int posX, posY;
	//Set all all of the classes values to zero so we can set everything manually
	RtlZeroMemory(&WindowClass, sizeof(&WindowClass));

	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.cbSize = sizeof(WindowClass);
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.hInstance = pInstance;
	WindowClass.lpfnWndProc = GameHandler;
	WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WindowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WindowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WindowClass.lpszMenuName = NULL;
	WindowClass.lpszClassName = "pEngine";

	if (!RegisterClassEx(&WindowClass))
		MessageBox(0,"Failed to register windows class.",0,0);
	
	if (FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&ScreenSettings, 0, sizeof(ScreenSettings));
		ScreenSettings.dmSize = sizeof(ScreenSettings);
		ScreenSettings.dmPelsWidth = (unsigned long)pHeight;
		ScreenSettings.dmPelsHeight = (unsigned long)pWidth;
		ScreenSettings.dmBitsPerPel = 32;
		ScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&ScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - pHeight) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - pWidth) / 2;
	}

	pHandle = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"pEngine",
		pTitle,
		WS_OVERLAPPEDWINDOW,
		posX, posY, pWidth, pHeight,
		NULL, NULL, pInstance, NULL);

	//Check if we successfully created the window!
	if (!pHandle) {
		MessageBox(0, "Failed to create window.", 0, 0);
		return false;
	}

	ShowWindow(pHandle, SW_SHOW);

	return true;
}
LRESULT pEngine::MsgHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}