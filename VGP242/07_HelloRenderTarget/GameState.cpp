#include "GameState.h"

using namespace KwurkEngine;
using namespace KwurkEngine::Math;
using namespace KwurkEngine::Graphics;
using namespace KwurkEngine::Core;
using namespace KwurkEngine::Input;


void GameState::Initialize()
{
	//MeshPX mesh = Meshbuilder::CreateSkySpherePX(30, 30, 100.0f);
	MeshPX mesh = Meshbuilder::CreateSpherePX(60, 60, 1.0f);

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

	//mDiffuseTexture.Initialize("../../Assets/Images/skysphere/space.jpg");
	mDiffuseTexture.Initialize("../../Assets/Images/planets/sun.jpg");
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
float gRotationYSpeed = 0.0f;

float gDistanceX = 0.0f;


void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);

	gRotationY += Math::Constants::HalfPi * deltaTime * gRotationYSpeed;
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
	if (input->IsKeyDown(KeyCode::S))
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

Matrix4 matWorldVar;

void GameState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	mDiffuseTexture.BindPS(0);
	mSampler.BindPS(0);

	//constantbuffer
	//Matrix4 matWorld = Matrix4::RotationY(gRotationY);
	//Matrix4 matWorld = Matrix4::RotationAxis(Vector3(gRotationYAxis, 1,1), gRotationY);
	Matrix4 matWorld = Matrix4::Translation(gDistanceX, 0, 0) * Matrix4::RotationAxis(Vector3(0, 1, 0), gRotationY);

	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);
	Matrix4 matWorldVar = matWorld;
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mMeshBuffer.Render();

	matWorld = Matrix4::Identity;
	matView = mRenderTargetCamera.GetViewMatrix();
	matProj = mRenderTargetCamera.GetProjectionMatrix();
	matFinal = matWorld * matView * matProj;
	wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mRenderTarget.BeginRender();
		mMeshBuffer.Render();
	mRenderTarget.EndRender();

}


bool buttonValue = false;
bool buttonValue2 = false;
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

	ImGui::Checkbox("Rings", &buttonValue);
	switch (buttonValue)
	{
		case true:
			SimpleDraw::AddGroundCircle(60, gDistanceX, Vector3(0, 0, 0), Colors::Red);	//For drawing rings of planet orbits
		break;
	default:
		break;
	}
	//combo box with all planets displayed
	ImGui::Checkbox("look at planet", &buttonValue2);
	switch (buttonValue2)
	{
	case true:
		//then	
		//mRenderTargetCamera.SetPosition(Vector3(matWorldVar._11, matWorldVar._22, matWorldVar._33));
		mRenderTargetCamera.SetLookAt(Vector3(matWorldVar._11, matWorldVar._22,matWorldVar._33));
		break;
	default:
		break;
	}
	if (ImGui::CollapsingHeader("RotationSpeed"))
	{
		ImGui::DragFloat("Distance from centerX", &gDistanceX, 0.001f);

		ImGui::DragFloat("Non-Independent", &gRotationYSpeed, 0.001f);
	}


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

