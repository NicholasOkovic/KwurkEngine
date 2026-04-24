#include "GameState.h"

using namespace KwurkEngine;
using namespace KwurkEngine::Math;
using namespace KwurkEngine::Graphics;
using namespace KwurkEngine::Core;
using namespace KwurkEngine::Input;


void GameState::Initialize()
{
	mGameWorld.AddService < CameraService>();
	mGameWorld.AddService < RenderService>();
	mGameWorld.Initialize();

	GameObject* transformGO = mGameWorld.CreateGameObject("Transform", L"../../Assets/Templates/Objects/transform_obj.json");
	transformGO->AddComponent<TransformComponent>();
	transformGO->Initialize();

	GameObject* cameraGO = mGameWorld.CreateGameObject("Camera", L"../../Assets/Templates/Objects/fps_camera.json");
	mCameraComponent = cameraGO->AddComponent<CameraComponent>();
	cameraGO->AddComponent<FPSCameraComponent>();
	cameraGO->Initialize();

	GameObject* playerGO = mGameWorld.CreateGameObject("Player", L"../../Assets/Templates/Objects/transform_obj.json");
	TransformComponent* playerTransform = playerGO->GetComponent<TransformComponent>();
	playerTransform->position.x = 2.0f;
	playerGO->Initialize();




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

