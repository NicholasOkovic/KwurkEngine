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
	
	std::filesystem::path shaderfile = L"../../Assets/Shaders/Standard.fx";	
	mStandardEffect.Initialize(shaderfile);
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.SetDirectionalLight(mDirectionalLight);

	shaderfile = L"../../Assets/Shaders/CelShading.fx";
	mRenderTargetStandardEffect.Initialize(shaderfile);
	mRenderTargetStandardEffect.SetCamera(mCamera);
	mRenderTargetStandardEffect.SetDirectionalLight(mDirectionalLight);

	mCharacter.Initialize(L"../../Assets/Models/Paladin/PaladinJNordstrom.model");
	mCharacter2.Initialize(L"../../Assets/Models/Character2/PumpkinhulkShaw.model");

	const uint32_t size = 512;
	mRenderTarget.Initialize(size, size, Texture::Format::RGBA_U8);
}

void GameState::Terminate()
{
	mRenderTarget.Terminate();
	mCharacter2.Terminate();
	mCharacter.Terminate();
	mRenderTargetStandardEffect.Terminate();
	mStandardEffect.Terminate();
	
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
bool viewCharacter1 = true;

void GameState::Render()
{
	mCamera.SetAspectRatio(1.0f);
	mRenderTarget.BeginRender();

	mRenderTargetStandardEffect.Begin();
	switch (viewCharacter1)
	{
	case true:
		mRenderTargetStandardEffect.Render(mCharacter2);
		break;

	case false:
		mRenderTargetStandardEffect.Render(mCharacter);
		break;
	default:
		break;
	}

	mRenderTargetStandardEffect.End();

	mRenderTarget.EndRender();

	mCamera.SetAspectRatio(0.0f);

	mStandardEffect.Begin();

	switch (viewCharacter1)
	{
	case true:
		mStandardEffect.Render(mCharacter);
		break;

	case false:
		mStandardEffect.Render(mCharacter2);
		break;
	default:
		break;
	}

	mStandardEffect.End();

	SimpleDraw::AddGroundPlane(10.0f, Colors::White);
	SimpleDraw::Render(mCamera);
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
	ImGui::Separator();
	ImGui::Text("RenderTarget");
	ImGui::Image(
		mRenderTarget.GetRawData(),
		{ 128, 128 },
		{ 0, 0 },
		{ 1, 1 },
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 });

	ImGui::Checkbox("Swap", &viewCharacter1);

	mStandardEffect.DebugUI();

	ImGui::End();
}

