////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Graphics.h"


GraphicsClass::GraphicsClass()
{
	pD3D = 0;
	pCamera = 0;
	pText = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
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
	pCamera = new CameraClass;
	if (!pCamera)
	{
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	pCamera->SetPosition(0.0f, 0.0f, -1.0f);
	pCamera->Render();
	pCamera->GetViewMatrix(baseViewMatrix);

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


void GraphicsClass::Shutdown()
{
	// Release the text object.
	if (pText)
	{
		pText->Shutdown();
		delete pText;
		pText = 0;
	}

	// Release the camera object.
	if (pCamera)
	{
		delete pCamera;
		pCamera = 0;
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


bool GraphicsClass::Frame(int fps, int cpu, float frameTime)
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
	pCamera->SetPosition(0.0f, 0.0f, -10.0f);

	return true;
}


bool GraphicsClass::Render()
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	pD3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	pCamera->Render();

	// Get the view, projection, and world matrices from the camera and D3D objects.
	pCamera->GetViewMatrix(viewMatrix);
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