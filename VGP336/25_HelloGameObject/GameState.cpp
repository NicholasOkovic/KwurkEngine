#include "GameState.h"

using namespace KwurkEngine;
using namespace KwurkEngine::Math;
using namespace KwurkEngine::Graphics;
using namespace KwurkEngine::Core;
using namespace KwurkEngine::Input;


void GameState::Initialize()
{
	mGameWorld.Initialize();

	GameObject* transformGO = mGameWorld.CreateGameObject("Transform");
	transformGO->AddComponent<TransformComponent>();
	transformGO->Initialize();

	GameObject* cameraGO = mGameWorld.CreateGameObject("Camera");
	mCameraComponent = cameraGO->AddComponent<CameraComponent>();
	cameraGO->AddComponent<FPSCameraComponent>();
	cameraGO->Initialize();

	GameObject* playerGO = mGameWorld.CreateGameObject("Player");
	TransformComponent* playerTransform = playerGO->AddComponent<TransformComponent>();
	playerTransform->position.x = 2.0f;
	playerGO->Initialize();


	GameObject* rockGO = mGameWorld.CreateGameObject("Rock");
	TransformComponent* rockTransform = rockGO->AddComponent<TransformComponent>();
	rockTransform->position.z = 10.0f;
	rockTransform->position.x = 2.0f;
	rockGO->Initialize();

	GameObject* treeGO = mGameWorld.CreateGameObject("Tree");
	TransformComponent* treeTransform = treeGO->AddComponent<TransformComponent>();
	treeTransform->position.z = 10.0f;
	treeTransform->position.y = 2.0f;
	treeGO->Initialize();

	GameObject* waterGO = mGameWorld.CreateGameObject("Water");
	TransformComponent* waterTransform = waterGO->AddComponent<TransformComponent>();
	waterTransform->position.z = 10.0f;
	waterTransform->position.x = -2.0f;
	waterGO->Initialize();

	GameObject* stickGO = mGameWorld.CreateGameObject("Stick");
	TransformComponent* stickTransform = stickGO->AddComponent<TransformComponent>();
	stickTransform->position.z = 10.0f;
	stickTransform->position.y = 1.0f;
	stickTransform->position.x = -4.0f;
	stickGO->Initialize();


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
	ImGui::End();

	SimpleDraw::Render(mCameraComponent->GetCamera());
}

