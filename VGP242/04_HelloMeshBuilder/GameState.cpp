#include "GameState.h"

using namespace KwurkEngine;
using namespace KwurkEngine::Math;
using namespace KwurkEngine::Graphics;
using namespace KwurkEngine::Core;
using namespace KwurkEngine::Input;



void CreateShape()
{


}


void GameState::Initialize()
{
	//simple shape in NDC space (-1/1, -1/1, 0/1)

	//CreateShape();

		//Vertices for each face(6 for each)

	MeshPC mesh = Meshbuilder::CreateSpherePC(30, 30, 1.0f);
	
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mMeshBuffer.Initialize<MeshPC>(mesh);

	mConstantBuffer.Initialize(sizeof(Matrix4));

	

	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTransform.fx";
	mVertexShader.Initialize(shaderFile, Graphics::VE_Position | VE_Color);
	mPixelShader.Initialize(shaderFile);
}

void GameState::Terminate()
{
	mPixelShader.Terminate();
	mVertexShader.Terminate();
	mConstantBuffer.Terminate();
	mMeshBuffer.Terminate();
}
float gRotationY = 0.0f;
float gRotationX = 0.0f;

void GameState::Update(float deltaTime)
{
	gRotationY += Math::Constants::HalfPi * deltaTime * 0.5f;
	gRotationX += Math::Constants::HalfPi * deltaTime * 0.25f;
} 

void GameState::Render()
{
	mVertexShader.Bind();
	mPixelShader.Bind();

	//constantbuffer
	Matrix4 matWorld = Matrix4::RotationY(gRotationY) * Matrix4::RotationX(gRotationX);
	Matrix4 matView = mCamera.GetViewMatrix();
	Matrix4 matProj = mCamera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);
	mConstantBuffer.Update(&wvp);
	mConstantBuffer.BindVS(0);
	mMeshBuffer.Render();

}




