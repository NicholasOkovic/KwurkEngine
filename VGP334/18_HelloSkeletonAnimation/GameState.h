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
	KwurkEngine::Graphics::DirectionalLight mDirectionalLight;
	KwurkEngine::Graphics::StandardEffect mStandardEffect;
	
	KwurkEngine::Graphics::RenderGroup mCharacter;
	KwurkEngine::Graphics::Animator mCharacterAnimator;

	KwurkEngine::Graphics::RenderObject mGround;

	bool mShowSkeleton = false;
	int mAnimationIndex = -1;
};






