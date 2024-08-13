#pragma once

#include <KwurkEngine/Inc/KwurkEngine.h>

class ShapeState : public KwurkEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	virtual void CreateShape();

	struct Vertex
	{
		KwurkEngine::Math::Vector3 position;
		KwurkEngine::Color color;

	};

	using Vertices = std::vector<Vertex>;
	Vertices mVertices;

	KwurkEngine::Graphics::Camera mCamera;
	KwurkEngine::Graphics::ConstantBuffer mConstantBuffer;
	KwurkEngine::Graphics::MeshBuffer mMeshBuffer;
	KwurkEngine::Graphics::VertexShader mVertexShader;
	KwurkEngine::Graphics::PixelShader mPixelShader;
};






