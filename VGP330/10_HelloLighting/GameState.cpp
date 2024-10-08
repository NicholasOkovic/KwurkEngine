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

	Mesh mesh = Meshbuilder::CreateSphere(30, 30, 1.0f);
	float x = -5.0f;
	for (int i = 0; i < 9; i++)
	{
		RenderObject& planet = mPlanets.emplace_back();
		mPlanet.meshBuffer.Initialize(mesh);
		mPlanet.diffuseTextureId = TextureCache::Get()->LoadTexture("misc/basketball.jpg");
		mPlanet.transform.position.x = x;
		x += 1.0f;
	}
	
	std::filesystem::path shaderfile = L"../../Assets/Shaders/DoTexture.fx";	
	mStandardEffect.Initialize(shaderfile);
	mStandardEffect.SetCamera(mCamera);
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
	else if(input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed);
	}
}

Vector3 minExtents = Vector3::Zero;
Vector3 maxExtents = Vector3::Zero;
Vector3 centerPos = Vector3::Zero;
Color lineColor = Colors::Green;

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

}

