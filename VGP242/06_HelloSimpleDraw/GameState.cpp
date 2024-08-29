#include "GameState.h"

using namespace KwurkEngine;
using namespace KwurkEngine::Math;
using namespace KwurkEngine::Graphics;
using namespace KwurkEngine::Core;
using namespace KwurkEngine::Input;

const char* gDrawTypeNames[] =
{
	"None",
	"Line",
	"Sphere"
};

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -3.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });
}

void GameState::Terminate()
{
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
	if (mDebugDrawType == DebugDrawType::Sphere)
	{
		SimpleDraw::AddSphere();
	}
	else if (mDebugDrawType == DebugDrawType::Line)
	{
		SimpleDraw::AddSphere();
	}

	SimpleDraw::AddLine({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, Colors::Green);
	SimpleDraw::Render(mCamera);
}

void GameState::DebugUI()
{
	ImGui::Begin("debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	int currentShape = static_cast<int>(mDebugDrawType);
	if (ImGui::Combo("DrawType", &currentDrawType, gDrawTypeNames, static_cast<int>(std::size(gDrawTypeNames))))
	{
		mDebugDrawType = (DebugDrawType)currentDrawType;
	}
	if (mDebugDrawType == DebugDrawType::Sphere)
	{

	}
	else if (mDebugDrawType == DebugDrawType::Line)
	{
		ImGui::DragFloat3("StartPos" & minExtents.x, 0.1f);
		ImGui::DragFloat3("CenterPos" & maxExtents.x, 0.1f);
	}

	ImGui::DragFloat3("endPos" &endPos.x, 0.1f);
	ImGui::ColorEdit3("Color" &lineColor.r);

	ImGui::End();
}

