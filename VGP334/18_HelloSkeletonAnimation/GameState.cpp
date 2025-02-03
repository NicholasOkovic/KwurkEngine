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

	mCharacter.Initialize(L"../../Assets/Models/Paladin/PaladinJNordstrom.model", &mCharacterAnimator);
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Paladin/Taunt.animset"); 
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Animations/Joyful_Jump.animset"); 
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Animations/Capoeira.animset"); 
	ModelCache::Get()->AddAnimation(mCharacter.modelId, L"../../Assets/Models/Animations/Walk_Forward.animset"); 
	
	mCharacterAnimator.Initialize(mCharacter.modelId);

	Mesh groundMesh = MeshBuilder::CreateGroundPlane(10, 10, 1.0f);
	mGround.meshBuffer.Initialize(groundMesh);
	mGround.diffuseMapId = TextureCache::Get()->LoadTexture("misc/concrete.jpg");
	mGround.material.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
	mGround.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mGround.material.specular = { 0.8f, 0.8f, 0.8f, 1.0f };
	mGround.material.power = 20.0f;

}

void GameState::Terminate()
{
	mGround.Terminate();
	mCharacter.Terminate();
	
	mStandardEffect.Terminate();
	
}

void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);

	mCharacterAnimator.Update(deltaTime);
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
	mStandardEffect.Begin();
	if (mShowSkeleton)
	{
		AnimationUtil::BoneTransforms boneTransforms;
		AnimationUtil::ComputeBoneTransforms(mCharacter.modelId, boneTransforms, &mCharacterAnimator);
		AnimationUtil::DrawSkeleton(mCharacter.modelId, boneTransforms);
	}
	else
	{
		mStandardEffect.Render(mCharacter);
	}
		mStandardEffect.Render(mGround);
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
	ImGui::Checkbox("ShowSkeleton", &mShowSkeleton);
	mStandardEffect.DebugUI();

	int maxAnimations = mCharacterAnimator.GetAnimationCount();
	if (ImGui::DragInt("AnimIndex", &mAnimationIndex, 1, -1, maxAnimations - 1))
	{
		mCharacterAnimator.PlayAnimation(mAnimationIndex, true);
	}
	ImGui::End();

	SimpleDraw::Render(mCamera);
}

