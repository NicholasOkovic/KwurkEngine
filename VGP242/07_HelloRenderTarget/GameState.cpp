#include "GameState.h"

using namespace KwurkEngine;
using namespace KwurkEngine::Math;
using namespace KwurkEngine::Graphics;
using namespace KwurkEngine::Core;
using namespace KwurkEngine::Input;


void GameState::Initialize()
{


	MeshPX mesh = Meshbuilder::CreateSkySpherePX(30, 30, 100.0f);
	
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	mRenderTargetCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mRenderTargetCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	mRenderTargetCamera.SetAspectRatio(1.0f);

	mMeshBuffer.Initialize<MeshPX>(mesh);

	mConstantBuffer.Initialize(sizeof(Matrix4));

	

	//std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTransform.fx";
	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTexture.fx";
	mVertexShader.Initialize<VertexPX>(shaderFile);
	mPixelShader.Initialize(shaderFile);

	mDiffuseTexture.Initialize("../../Assets/Images/skysphere/sky.jpg");
	//mDiffuseTexture.Initialize("../../Assets/Images/skybox/skybox.jpg");
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

	constexpr uint32_t size = 512;
	mRenderTarget.Initialize(size, size, Texture::Format::RGBA_U32);
}

void GameState::Terminate()
{
	mSampler.Terminate();
	mDiffuseTexture.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mConstantBuffer.Terminate();
	mMeshBuffer.Terminate();
}
float gRotationY = 0.0f;
float gRotationX = 0.0f;

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
	else if (input->IsKeyDown(KeyCode::S))
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

void GameState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	mDiffuseTexture.BindPS(0);
	mSampler.BindPS(0);



	//constantbuffer
	Matrix4 matWorld = Matrix4::RotationY(gRotationY) * Matrix4::RotationX(gRotationX);
	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mMeshBuffer.Render();

	Matrix4 matWorld = Matrix4::RotationY(gRotationY) * Matrix4::RotationX(gRotationX);
	Matrix4 matView = mRenderTargetCamera.GetViewMatrix();
	Matrix4 matProj = mRenderTargetCamera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mRenderTarget.BeginRender();
		mMeshBuffer.Render();
	mRenderTarget.EndRender();




	
}


bool buttonValue = false;
int intValue = 1;

void GameState::DebugUI()
{
	SimpleDraw::AddGroundPlane(10.0f, Colors::White);
	SimpleDraw::Render(mCamera);

	ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Image(
		mRenderTarget.GetRawData(),
		{ 256, 256 },
		{ 0,0 },
		{ 1,1 },
		{ 1,1, 1, 1 },
		{ 1,1, 1, 1 });
	ImGui::End();

	//ImGui::LabelText("TestLAble", "THis is a cool label");
	//ImGui::Checkbox("testButton", &buttonValue);
	//ImGui::DragInt("TestDrag", &intValue, 1, 0, 100);
	//if (ImGui::CollapsingHeader("Rotation"))
	//{
	//	ImGui::DragFloat("RotationY", &gRotationY, 0.001f);
	//	ImGui::DragFloat("RotationX", &gRotationX, 0.001f);
	//}

}

