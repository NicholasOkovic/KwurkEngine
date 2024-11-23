#include "GameState.h"

using namespace KwurkEngine;
using namespace KwurkEngine::Math;
using namespace KwurkEngine::Graphics;
using namespace KwurkEngine::Core;
using namespace KwurkEngine::Input;


void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mDirectionalLight.direction = Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
	mDirectionalLight.diffuse = { 0.7f, 0.7f, 0.7f, 1.0f };
	mDirectionalLight.specular = { 0.9f, 0.9f, 0.9f, 1.0f };

	Mesh mesh = MeshBuilder::CreateSphere(30, 30, 1.0f);
	float x = -5.0f;
	for (int i = 0; i < 3; i++)
	{
		RenderObject& planet = mPlanets.emplace_back();
		planet.meshBuffer.Initialize(mesh);
		planet.diffuseMapId = TextureCache::Get()->LoadTexture("misc/rock/Old_Rocks_DIFF.png");
		planet.normalMapId = TextureCache::Get()->LoadTexture("misc/rock/Old_Rocks_NRM.png");
		planet.specMapId = TextureCache::Get()->LoadTexture("misc/rock/Old_Rocks_SPEC.png");
		planet.bumpMapId = TextureCache::Get()->LoadTexture("misc/rock/Old_Rocks_BMP.png");
		planet.transform.position.x = x;
		x += 2.0f;
	}
	
	std::filesystem::path shaderfile = L"../../Assets/Shaders/CelShading.fx";	
	mStandardEffect.Initialize(shaderfile);
	mStandardEffect.SetCamera(mCamera);

	mStandardEffect.SetDirectionalLight(mDirectionalLight);
}

void GameState::Terminate()
{
	mStandardEffect.Terminate();
	for (RenderObject& planet : mPlanets)
	{
		planet.Terminate();
	}
}

void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);
} 


void GameState::UpdateCamera(float deltaTime)
{
	auto input = InputSystem::Get();
	const float moveSpeed = (input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f) * deltaTime;
	const float turnSpeed = 0.1 * deltaTime;

	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed);
	}
	if(input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed);
	}
	if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed);
	}
}

//Vector3 minExtents = Vector3::Zero;
//Vector3 maxExtents = Vector3::Zero;
//Vector3 centerPos = Vector3::Zero;
//Color lineColor = Colors::Green;

void GameState::Render()
{
	mStandardEffect.Begin();
	for (RenderObject& planet : mPlanets)
	{
		mStandardEffect.Render(planet);
	}
	mStandardEffect.End();
}

void GameState::DebugUI()
{
	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Direction", &mDirectionalLight.direction.x, 0.01f))
		{
			mDirectionalLight.direction = Normalize(mDirectionalLight.direction);
		}
		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);

	}
	if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorEdit4("Ambient##Material", &mPlanets[0].material.ambient.r);
		ImGui::ColorEdit4("Diffuse##Material", &mPlanets[0].material.diffuse.r);
		ImGui::ColorEdit4("Specular##Material", &mPlanets[0].material.specular.r);
		ImGui::ColorEdit4("Emissive##Material", &mPlanets[0].material.emissive.r);
		ImGui::DragFloat("SpecPower##Material", &mPlanets[0].material.power, 0.01f, 0.0f, 10000.0f);;
	}

	mStandardEffect.DebugUI();


	ImGui::End();
}

