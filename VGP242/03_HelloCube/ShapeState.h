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

	ID3D11Buffer* mVertexBuffer = nullptr;
	ID3D11VertexShader* mVertexShader = nullptr;
	ID3D11InputLayout* mInputLayout = nullptr;
	ID3D11PixelShader* mPixelShader = nullptr;
};






