#include "GameState.h"

using namespace KwurkEngine;
using namespace KwurkEngine::Math;
using namespace KwurkEngine::Graphics;
using namespace KwurkEngine::Core;
using namespace KwurkEngine::Input;

const char* mPlanetNames[] =
{
	"Sun",
	"Mercury",
	"Venus",
	"Earth",
	"Mars",
	"Jupiter",
	"Saturn",
	"Uranus",
	"Neptune",
	"Pluto"
};


void GameState::Initialize()
{
	MeshPX meshes[11]; //11

	//all the planets
	//Actual size of planets / 1000 rounded(minus the sun)
	meshes[0] = MeshBuilder::CreateSpherePX(60, 60, 1.0f);	//Sun
	meshes[1] = MeshBuilder::CreateSpherePX(60, 60, 0.03f);	//Mercury
	meshes[2] = MeshBuilder::CreateSpherePX(60, 60, 0.1f);	//Venus
	meshes[3] = MeshBuilder::CreateSpherePX(60, 60, 0.12f);	//Earth
	meshes[4] = MeshBuilder::CreateSpherePX(60, 60, 0.05f);	//Mars
	meshes[5] = MeshBuilder::CreateSpherePX(60, 60, 1.0f);	//Jupiter
	meshes[6] = MeshBuilder::CreateSpherePX(60, 60, 1.0f);	//Saturn
	meshes[7] = MeshBuilder::CreateSpherePX(60, 60, 0.4f);	//Uranus
	meshes[8] = MeshBuilder::CreateSpherePX(60, 60, 0.4f);	//Neptune
	meshes[9] = MeshBuilder::CreateSpherePX(60, 60, 0.03f);	//Pluto
	meshes[10] = MeshBuilder::CreateSkySpherePX(60, 60, 50.0f); //space





	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	mRenderTargetCamera.SetPosition({ 0.0f, 1.0f, -2.0f });
	mRenderTargetCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
	mRenderTargetCamera.SetAspectRatio(1.0f);

	for (int i = 0; i < 11; i++)
	{
		mPlanets[i].mMeshBuffer.Initialize<MeshPX>(meshes[i]);
	}


	mConstantBuffer.Initialize(sizeof(Matrix4));

	//std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTransform.fx";
	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTexture.fx";


	mVertexShader.Initialize<VertexPX>(shaderFile);
	mPixelShader.Initialize(shaderFile);

	//actual orbital values / 50
	//not actual distance from sun(they were too far apat)
	mPlanets[0].mDiffuseTexture.Initialize("../../Assets/Images/planets/sun.jpg");
	mPlanets[0].orbitSpeed = 0;
	mPlanets[0].distanceFromSun = 0;
	mPlanets[0].rotationSpeed = 0.05;

	mPlanets[1].mDiffuseTexture.Initialize("../../Assets/Images/planets/mercury.jpg");
	mPlanets[1].orbitSpeed = 1.0f;
	mPlanets[1].distanceFromSun = 1.5f;
	mPlanets[1].rotationSpeed = 0.01;

	mPlanets[2].mDiffuseTexture.Initialize("../../Assets/Images/planets/venus.jpg");
	mPlanets[2].orbitSpeed = 0.7f;
	mPlanets[2].distanceFromSun = 1.9f;
	mPlanets[2].rotationSpeed = 0.01;

	mPlanets[3].mDiffuseTexture.Initialize("../../Assets/Images/planets/earth/earth.jpg");
	mPlanets[3].orbitSpeed = 0.6f;
	mPlanets[3].distanceFromSun = 2.3f;
	mPlanets[3].rotationSpeed = 0.6;

	mPlanets[4].mDiffuseTexture.Initialize("../../Assets/Images/planets/mars.jpg");
	mPlanets[4].orbitSpeed = 0.5f;
	mPlanets[4].distanceFromSun = 2.6f;
	mPlanets[4].rotationSpeed = 0.5;

	mPlanets[5].mDiffuseTexture.Initialize("../../Assets/Images/planets/jupiter.jpg");
	mPlanets[5].orbitSpeed = 0.25f;
	mPlanets[5].distanceFromSun = 4.20f;
	mPlanets[5].rotationSpeed = 2;

	mPlanets[6].mDiffuseTexture.Initialize("../../Assets/Images/planets/saturn.jpg");
	mPlanets[6].orbitSpeed = 0.2f;
	mPlanets[6].distanceFromSun = 7.54f;
	mPlanets[6].rotationSpeed = 1.6;

	mPlanets[7].mDiffuseTexture.Initialize("../../Assets/Images/planets/uranus.jpg");
	mPlanets[7].orbitSpeed = 0.12f;
	mPlanets[7].distanceFromSun = 10.0f;
	mPlanets[7].rotationSpeed = 0.8;

	mPlanets[8].mDiffuseTexture.Initialize("../../Assets/Images/planets/neptune.jpg");
	mPlanets[8].orbitSpeed = 0.1f;
	mPlanets[8].distanceFromSun = 11.5f;
	mPlanets[8].rotationSpeed = 0.4;

	mPlanets[9].mDiffuseTexture.Initialize("../../Assets/Images/planets/pluto.jpg");
	mPlanets[9].orbitSpeed = 0.05f;
	mPlanets[9].distanceFromSun = 13.4f;
	mPlanets[9].rotationSpeed = 0.001;

	mPlanets[10].mDiffuseTexture.Initialize("../../Assets/Images/skysphere/space.jpg");
	mPlanets[10].orbitSpeed = 0;
	mPlanets[10].distanceFromSun = 0;
	mPlanets[10].rotationSpeed = 0.0005;


	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);

	constexpr uint32_t size = 512;
	mRenderTarget.Initialize(size, size, Texture::Format::RGBA_U32);
}

void GameState::Terminate()
{
	mSampler.Terminate();
	for (int i = 10; i >= 0; i--)	
	{
		mPlanets[i].mDiffuseTexture.Terminate();
	}
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mConstantBuffer.Terminate();
	for (int l = 10; l >= 0; l--)
	{
		mPlanets[l].mMeshBuffer.Terminate();
	}

}

float gRotation[11];	
float gLocalRotation[11];	

float gRotationModifier = 1.0f;
float gLocalRotationModifier = 1.0f;
int p = 1;

void GameState::Update(float deltaTime)
{
	UpdateCamera(deltaTime);

	for (int i = 0; i < 11; i++)	
	{
		gRotation[i] += Math::Constants::HalfPi * deltaTime * mPlanets[i].orbitSpeed * gRotationModifier;
		gLocalRotation[i] += Math::Constants::HalfPi * deltaTime * mPlanets[i].rotationSpeed * gLocalRotationModifier;
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
	mSampler.BindPS(0);

	mPlanets[0].mDiffuseTexture.BindPS(0);
	mSampler.BindPS(0);

	Matrix4 matWorld = Matrix4::RotationY(gLocalRotation[0]);
	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);

	mPlanets[0].mMeshBuffer.Render();


	for (int i = 0; i < 11; i++)
	{
		mPlanets[i].mDiffuseTexture.BindPS(0);

		matWorld = Matrix4::RotationY(gLocalRotation[i]) * Matrix4::Translation(mPlanets[i].distanceFromSun, 0, 0) * Matrix4::RotationAxis(Vector3(0, 1, 0), gRotation[i]);

		matWorldVar = matWorld;

		matView = mCamera.GetViewMatrix();
		matProj = mCamera.GetProjectionMatrix();
		matFinal = matWorld * matView * matProj;
		wvp = Transpose(matFinal);
		mConstantBuffer.Update(&wvp);
		mConstantBuffer.BindVS(0);

		mPlanets[i].mMeshBuffer.Render();
	}

	Matrix4 matWorldR = Matrix4::Identity;
	Matrix4 matViewR = mRenderTargetCamera.GetViewMatrix();
	Matrix4 matProjR = mRenderTargetCamera.GetProjectionMatrix();
	Matrix4 matFinalR = matWorldR * matViewR * matProjR;
	Matrix4 wvpR = Transpose(matFinalR);
	mConstantBuffer.Update(&wvpR);
	mConstantBuffer.BindVS(0);

	mRenderTarget.BeginRender();

	mPlanets[p].mDiffuseTexture.BindPS(0);

	mPlanets[p].mMeshBuffer.Render();

	mRenderTarget.EndRender();
}


bool viewRings = false;
bool viewPlanet = false;


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

	if (ImGui::Combo("Planet", &p, mPlanetNames, static_cast<int>(std::size(mPlanetNames))))
	{
		//mRenderTargetCamera.SetLookAt(Vector3(mPlanets[p].transform._41, mPlanets[p].transform._42, mPlanets[p].transform._43));
		mRenderTargetCamera.SetLookAt(Vector3(0,0,0));
	}


	ImGui::Checkbox("Rings", &viewRings);
	switch (viewRings)
	{
		case true:
			for (int i = 0; i < 10; i++)
			{
				SimpleDraw::AddGroundCircle(60, mPlanets[i].distanceFromSun, Vector3(0, 0, 0), Colors::Red);	//For drawing rings of planet orbits
			}
		break;
	default:
		break;
	}
	if (ImGui::CollapsingHeader("RotationSpeed"))
	{
		ImGui::DragFloat("Orbit speed Modifier", &gRotationModifier, 0.001f);
		ImGui::DragFloat("Local rot Modifier", &gLocalRotationModifier, 0.001f);
	}
	ImGui::End();
}

