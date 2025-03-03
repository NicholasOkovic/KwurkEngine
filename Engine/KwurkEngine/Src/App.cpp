#include "Precompiled.h"
#include "App.h"
#include "AppState.h"
#include "EventManager.h"

using namespace KwurkEngine;
using namespace KwurkEngine::Core;
using namespace KwurkEngine::Graphics;
using namespace KwurkEngine::Input;
using namespace KwurkEngine::Physics;
using namespace KwurkEngine::Audio;

void App::Run(const AppConfig& config)
{
	Window myWindow;
	myWindow.Initialize(
		GetModuleHandle(nullptr),
		config.appName,
		config.winWidth,
		config.winHeight
	);
	ASSERT(myWindow.IsActive(), "App: failed to create world");

	//init singletons
	auto handle = myWindow.GetWindowHandle();
	GraphicsSystem::StaticInitialize(handle, false);
	InputSystem::StaticInitialize(handle);
	DebugUI::StaticInitialize(handle, false, true);
	SimpleDraw::StaticInitialize(config.maxDrawLines);
	TextureCache::StaticInitialize("../../Assets/Images/");
	ModelCache::StaticInitialize();
	EventManager::StaticInitialize();
	AudioSystem::StaticInitialize();
	SoundEffectManager::StaticInitialize("../../Assets/Sounds/");


	PhysicsWorld::Settings settings;
	PhysicsWorld::StaticInitialize(settings);

	// start state
	ASSERT(mCurrentState != nullptr, "App: current state is available");
	mCurrentState->Initialize();

	//GraphicsSystem::Get()->SetClearColor(Colors::Pink);
	GraphicsSystem* gs = GraphicsSystem::Get();	
	InputSystem * input = InputSystem::Get();

	//run program
	mRunning = true;
	while (mRunning)
	{
		myWindow.ProcessMessage();
		input->Update();
		if (!myWindow.IsActive() || input->IsKeyPressed(KeyCode::ESCAPE))
		{
			Quit();
			break;
		}

		AudioSystem::Get()->Update();

		if (mNextState != nullptr)
		{
			mCurrentState->Terminate();
			mCurrentState = std::exchange(mNextState, nullptr);
			mCurrentState->Initialize();
		}

		float deltaTime = TimeUtil::GetDeltaTime();
#ifdef _DEBUG
		if (deltaTime < 0.5f)
#endif
		{
			mCurrentState->Update(deltaTime);
			PhysicsWorld::Get()->Update(deltaTime);
		}

		gs->BeginRender();
			mCurrentState->Render();
			DebugUI::BeginRender();
				mCurrentState->DebugUI();
			DebugUI::EndRender();
		gs->EndRender();
	}
	//end state
	mCurrentState->Terminate();


	//terminate singletons
	PhysicsWorld::StaticTerminate();
	SoundEffectManager::StaticTerminate();
	AudioSystem::StaticTerminate();
	EventManager::StaticTerminate();
	ModelCache::StaticTerminate();
	TextureCache::StaticTerminate();
	SimpleDraw::StaticTerminate();
	DebugUI::StaticTerminate();
	InputSystem::StaticTerminate();
	GraphicsSystem::StaticTerminate();
	myWindow.Terminate();
}

void App::Quit()
{
	mRunning = false;
}

void App::ChangeState(const std::string& stateName)
{
	auto iter = mAppStates.find(stateName);
	if (iter != mAppStates.end())
	{
		mNextState = iter->second.get();
	}


}
