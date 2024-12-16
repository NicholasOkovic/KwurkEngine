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
	KwurkEngine::Graphics::ShadowEffect mShadowEffect;

	KwurkEngine::Graphics::PostProcessingEffect mPostProcessingEffect;
	//KwurkEngine::Graphics::RenderTarget mRenderTarget;

	KwurkEngine::Graphics::RenderGroup mCharacter;
	KwurkEngine::Graphics::RenderObject mGround;

};






