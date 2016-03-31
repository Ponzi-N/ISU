#include <windows.h>
#include "Core.h"

class Beta : public pEngine
{
public:
	Beta(HINSTANCE hInstance);
	virtual ~Beta();


	bool InitializeEngine() override;
	virtual void Tick(float DeltaTime) override;
	virtual void RenderEngine() override;
};

Beta::Beta(HINSTANCE hInstance) :pEngine(hInstance)
{

}

Beta::~Beta()
{

}

bool Beta::InitializeEngine()
{
	if (!pEngine::InitializeEngine())
		return false;

	return true;
}

void Beta::Tick(float DeltaTime)
{
	bool result;

	// Update the system stats.
	Timer->Frame();
	Fps->Frame();
	Cpu->Frame();

	// Do the input frame processing.
	result = Input->Frame();
	if (!result)
	{
		return;
	}

	// Do the frame processing for the graphics object.
	result = Graphics->Frame(Fps->GetFps(), Cpu->GetCpuPercentage(), Timer->GetTime());
	if (!result)
	{
		return;
	}

	// Finally render the graphics to the screen.
	result = Graphics->Render();
	if (!result)
	{
		return;
	}

	return;
}
void Beta::RenderEngine()
{
	
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	Beta* BetaGame = new Beta(hInstance);
	if (!BetaGame->InitializeEngine())
		return 1;

	return BetaGame->RunEngine();

	return 1;
}