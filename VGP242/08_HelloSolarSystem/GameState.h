#pragma once

#include <KwurkEngine/Inc/KwurkEngine.h>


struct StructObject
{
	KwurkEngine::Math::Matrix4 transform;


	KwurkEngine::Graphics::MeshBuffer mMeshBuffer;
	KwurkEngine::Graphics::Texture mDiffuseTexture;



	float localRotation;

	float distanceFromSun;
	float orbitSpeed;
	float rotationSpeed;
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

	StructObject mPlanets[11];

	KwurkEngine::Graphics::Camera mCamera;
	KwurkEngine::Graphics::Camera mRenderTargetCamera;
	KwurkEngine::Graphics::ConstantBuffer mConstantBuffer;
	KwurkEngine::Graphics::MeshBuffer mMeshBuffer;
	KwurkEngine::Graphics::VertexShader mVertexShader;
	KwurkEngine::Graphics::PixelShader mPixelShader;
	KwurkEngine::Graphics::Texture mDiffuseTexture;
	KwurkEngine::Graphics::Sampler mSampler;
	KwurkEngine::Graphics::RenderTarget mRenderTarget;
};






