#pragma once

#include <KwurkEngine/Inc/KwurkEngine.h>

enum class DebugDrawType
{
	None,
	Line,
	Sphere
};


class GameState : public KwurkEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

protected:
	void UpdateCamera(float deltaTime);
	KwurkEngine::Graphics::Camera mCamera;
	DebugDrawType mDebugDrawType = DebugDrawType::None;

};






