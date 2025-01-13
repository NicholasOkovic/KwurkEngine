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

	Mesh ball = MeshBuilder::CreateSphere(60, 60, 0.5f);
	mBall.meshBuffer.Initialize(ball);
	mBall.diffuseMapId = TextureCache::Get()->LoadTexture("misc/basketball.jpg");

	Mesh ground = MeshBuilder::CreateGroundPlane(10, 10, 1.0f);
	mGround.meshBuffer.Initialize(ground);
	mGround.diffuseMapId = TextureCache::Get()->LoadTexture("misc/concrete.jpg");

	Mesh wall = MeshBuilder::CreateGroundPlane(10, 5, 1.0f);
	mWall.meshBuffer.Initialize(wall);
	mWall.diffuseMapId = TextureCache::Get()->LoadTexture("misc/concrete.jpg");

	mWall.transform.position.x += 5.1;
	mWall.transform.position.y += 2.5;
	mWall.transform.rotation.z = 40.0f * Math::Constants::DegToRad;

	mAnimationTime = 0.0f;

	mAnimation = AnimationBuilder()
		.AddPositionKey({ 0.0f, 2.5f, 0.0f }, 0.0f)
		.AddPositionKey({ 1.25f, 0.25f, 0.0f }, 1.0f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 0.8f)
		.AddScaleKey({ 0.5f, 1.5f, 1.5f }, 1.0f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 1.2f)

		.AddPositionKey({ 2.5f, 2.5f, 0.0f }, 2.0f)
		.AddPositionKey({ 3.75f, 0.25f, 0.0f }, 3.0f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 2.8f)
		.AddScaleKey({ 0.5f, 1.5f, 1.5f }, 3.0f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 3.2f)

		.AddPositionKey({ 5.0f, 2.5f, 0.0f }, 4.0f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 3.8f)
		.AddScaleKey({ 0.5f, 1.5f, 1.5f }, 4.0f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 4.2f)

		.AddPositionKey({ 3.75f, 0.25f, 0.0f }, 5.0f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 4.8f)
		.AddScaleKey({ 0.5f, 1.5f, 1.0f }, 5.0f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 5.2f)

		.AddPositionKey({ 2.5f, 2.5f, 0.0f }, 6.0f)
		.AddPositionKey({ 1.25f, 0.25f, 0.0f }, 7.0f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 6.8f)
		.AddScaleKey({ 0.5f, 1.5f, 1.5f }, 7.0f)
		.AddScaleKey({ 1.0f, 1.0f, 1.0f }, 7.2f)

		.AddPositionKey({ 0.0f, 2.5f, 0.0f }, 8.0f)


		.AddRotationKey( Quaternion::Identity, 0.0f )
		.AddRotationKey( Quaternion::CreateFromAxisAngle(Math::Vector3::ZAxis, 180.0f * Math::Constants::DegToRad), 2.0f)
		.AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::ZAxis, 360.0f * Math::Constants::DegToRad), 4.0f)
		.AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::ZAxis, 180.0f * Math::Constants::DegToRad), 6.0f)
		.AddRotationKey(Quaternion::CreateFromAxisAngle(Math::Vector3::ZAxis, 0.0f * Math::Constants::DegToRad), 8.0f)
		.Build();

}

void GameState::Terminate()
{
	mWall.Terminate();
	mGround.Terminate();
	mBall.Terminate();
	mStandardEffect.Terminate();
	
}

void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);
	if (mAnimation.GetDuration() > 0.0f)
	{
		mAnimationTime += deltaTime;
		while (mAnimationTime > mAnimation.GetDuration())
		{
			mAnimationTime -= mAnimation.GetDuration();
		}
	}
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
	mBall.transform = mAnimation.GetTranform(mAnimationTime);

	mStandardEffect.Begin();
	mStandardEffect.Render(mGround);
	mStandardEffect.Render(mBall);
	mStandardEffect.Render(mWall);
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

	mStandardEffect.DebugUI();

	ImGui::End();
}

