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

	//ball info
	KwurkEngine::Graphics::RenderObject mBall;
	KwurkEngine::Physics::CollisionShape mBallShape;
	KwurkEngine::Physics::RigidBody mBallRB;

	//ground info
	KwurkEngine::Graphics::RenderObject mGround;
	KwurkEngine::Physics::CollisionShape mGroundShape;
	KwurkEngine::Physics::RigidBody mGroundRB;

	struct BoxData
	{
		KwurkEngine::Graphics::RenderObject box;
		KwurkEngine::Physics::CollisionShape boxShape;
		KwurkEngine::Physics::RigidBody boxRB;
	};
	using Boxes = std::vector<BoxData>;
	Boxes mBoxes;


};






