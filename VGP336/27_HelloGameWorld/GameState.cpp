#include "GameState.h"
#include "CustomDebugDrawComponent.h"
#include "CustomDebugDrawService.h"

using namespace KwurkEngine;
using namespace KwurkEngine::Math;
using namespace KwurkEngine::Graphics;
using namespace KwurkEngine::Core;
using namespace KwurkEngine::Input;
using namespace KwurkEngine::Physics;

Service* MakeCustomService(const std::string& serviceName, GameWorld& gameWorld)
{
	if (serviceName == "CustomDebugDrawService")
	{
		return gameWorld.AddService<CustomDebugDrawService>();
	}

	//

	return nullptr;
}

Component* MakeCustomComponent(const std::string& componentName, GameObject& gameObject)
{
	if (componentName == "CustomDebugDrawComponent")
	{
		return gameObject.AddComponent<CustomDebugDrawComponent>();
	}

	//

	return nullptr;
}

Component* GetCustomComponent(const std::string& componentName, GameObject& gameObject)
{
	if (componentName == "CustomDebugDrawComponent")
	{
		return gameObject.GetComponent<CustomDebugDrawComponent>();
	}

	//

	return nullptr;
}
void GameState::Initialize()
{
	mLevelFile = L"../../Assets/Templates/Levels/level.json";

	//set a callabckj to try make a s vusotm service(any service that is not apat
	GameWorld::SetCustomService(MakeCustomService);
	//sets callback to try make/get a custom component ( any compononent NOT part of the engine)
	GameObjectFactory::SetCustomMake(MakeCustomComponent);
	GameObjectFactory::SetCustomGet(GetCustomComponent);

	mGameWorld.LoadLevel(mLevelFile);
}

void GameState::Terminate()
{
	mGameWorld.Terminate();
}

void GameState::Update(float deltaTime)
{
	mGameWorld.Update(deltaTime);
} 


void GameState::Render()
{
	mGameWorld.Render();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	mGameWorld.DebugUI();
	if (ImGui::Button("ReloadLevel"))
	{
		mGameWorld.Terminate();
		mGameWorld.LoadLevel(mLevelFile);
	}
	ImGui::End();
}

