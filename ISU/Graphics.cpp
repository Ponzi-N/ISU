#include "Graphics.h"


pGraphics::pGraphics()
{
	pD3D = 0;
	Camera = 0;
	pText = 0;
}


pGraphics::pGraphics(const pGraphics& other)
{
}


pGraphics::~pGraphics()
{
}


bool pGraphics::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	D3DXMATRIX baseViewMatrix;


	// Create the Direct3D object.
	pD3D = new D3DClass;
	if (!pD3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = pD3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, "Could not initialize Direct3D", "Error", MB_OK);
		return false;
	}

	// Create the camera object.
	Camera = new pCamera;
	if (!Camera)
	{
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	Camera->SetPosition(0.0f, 0.0f, -1.0f);
	Camera->Render();
	Camera->GetViewMatrix(baseViewMatrix);

	// Create the text object.
	pText = new TextClass;
	if (!pText)
	{
		return false;
	}

	// Initialize the text object.
	result = pText->Initialize(pD3D->GetDevice(), pD3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, "Could not initialize the text object.", "Error", MB_OK);
		return false;
	}

	return true;
}


void pGraphics::Shutdown()
{
	// Release the text object.
	if (pText)
	{
		pText->Shutdown();
		delete pText;
		pText = 0;
	}

	// Release the camera object.
	if (Camera)
	{
		delete Camera;
		Camera = 0;
	}

	// Release the D3D object.
	if (pD3D)
	{
		pD3D->Shutdown();
		delete pD3D;
		pD3D = 0;
	}

	return;
}


bool pGraphics::Frame(int fps, int cpu, float frameTime)
{
	bool result;


	// Set the frames per second.
	result = pText->SetFps(fps, pD3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the cpu usage.
	result = pText->SetCpu(cpu, pD3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}


	// Set the position of the camera.
	Camera->SetPosition(0.0f, 0.0f, -10.0f);

	return true;
}


bool pGraphics::Render()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	pD3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	Camera->Render();

	// Get the view, projection, and world matrices from the camera and D3D objects.
	Camera->GetViewMatrix(viewMatrix);
	pD3D->GetWorldMatrix(worldMatrix);
	pD3D->GetProjectionMatrix(projectionMatrix);
	pD3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	pD3D->TurnZBufferOff();

	// Turn on the alpha blending before rendering the text.
	pD3D->TurnOnAlphaBlending();

	// Render the text strings.
	result = pText->Render(pD3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	pD3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	pD3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	pD3D->EndScene();

	return true;
}