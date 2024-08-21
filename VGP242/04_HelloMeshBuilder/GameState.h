#pragma once

#include <KwurkEngine/Inc/KwurkEngine.h>

class GameState : public KwurkEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	KwurkEngine::Graphics::Camera mCamera;
	KwurkEngine::Graphics::ConstantBuffer mConstantBuffer;
	KwurkEngine::Graphics::MeshBuffer mMeshBuffer;
	KwurkEngine::Graphics::VertexShader mVertexShader;
	KwurkEngine::Graphics::PixelShader mPixelShader;
	KwurkEngine::Graphics::Texture mDiffuseTexture;
	KwurkEngine::Graphics::Sampler mSampler;
};






