#pragma once

#include <KwurkEngine/Inc/KwurkEngine.h>



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

	KwurkEngine::Graphics::RenderObject mBall;
	KwurkEngine::Graphics::RenderObject mGround;
	KwurkEngine::Graphics::RenderObject mWall;
	KwurkEngine::Graphics::DirectionalLight mDirectionalLight;
	KwurkEngine::Graphics::StandardEffect mStandardEffect;

	//animations
	KwurkEngine::Graphics::Animation mAnimation;
	float mAnimationTime = 0.0f;

};






