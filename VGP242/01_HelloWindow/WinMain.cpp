#include <KwurkEngine/Inc/KwurkEngine.h>

class GameState : public KwurkEngine::AppState
{
public:
	void Initialize() override
	{
		LOG("Game state Initialized");
	}
	void Terminate() override
	{
		LOG("Game state Terminated");
	}

private:
};


int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	KwurkEngine::AppConfig config;
	config.appName = L"Hello world";

	KwurkEngine::App& myApp = KwurkEngine::MainApp();
	myApp.AddState<GameState>("GameState");
	myApp.Run(config);

	return(0);
}