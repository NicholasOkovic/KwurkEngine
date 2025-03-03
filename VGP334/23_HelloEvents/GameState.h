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
	void OnMoveEvent();
	void OnSpacePressedEvent(const KwurkEngine::Event& e);

	KwurkEngine::Graphics::Camera mCamera;

	KwurkEngine::Graphics::RenderObject mBall;
	KwurkEngine::Graphics::RenderObject mGround;
	KwurkEngine::Graphics::RenderObject mWall;
	KwurkEngine::Graphics::DirectionalLight mDirectionalLight;
	KwurkEngine::Graphics::StandardEffect mStandardEffect;

	KwurkEngine::Math::Vector3 mOffset = { 0.0f, 0.0f, 0.0f };
	KwurkEngine::ListenerId mSpacePressedEventId = 0;
	KwurkEngine::Audio::SoundId mGunEventId = 0;
	KwurkEngine::Audio::SoundId mExplosionEventId = 0;

	//animations
	KwurkEngine::Graphics::Animation mAnimation;
	float mAnimationTime = 0.0f;

};






