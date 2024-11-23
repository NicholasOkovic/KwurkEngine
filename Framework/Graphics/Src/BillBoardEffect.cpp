#include "Precompiled.h"
#include "BillBoardEffect.h"

#include "Camera.h"
#include "RenderObject.h"
#include "TextureCache.h"
#include "VertexTypes.h"

using namespace KwurkEngine;
using namespace KwurkEngine::Graphics;

void BillBoardEffect::Initialize()
{
	std::filesystem::path shaderFile = L"../../Assets/Shaders/DoTexture.fx";
	mVertexShader.Initialize<VertexPX>(shaderFile);
	mPixelShader.Initialize(shaderFile);
	mTransformBuffer.Initialize();
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
	mBlendState.Initialize(BlendState::Mode::AlphaBlend);
}

void BillBoardEffect::Terminate()
{
	mBlendState.Terminate();
	mSampler.Terminate();
	mTransformBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
}

void BillBoardEffect::Begin()
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mBlendState.Set();
	mTransformBuffer.BindVS(0);
	mSampler.BindPS(0);
}

void BillBoardEffect::End()
{
	Texture::UnbindPS(0);
	BlendState::ClearState();
}

void BillBoardEffect::Render(const RenderObject& renderObject)
{
	Math::Matrix4 matView = mCamera->GetViewMatrix();
	Math::Matrix4 matWV = Math::Matrix4::Translation(Math::TransformCoord(renderObject.transform.position, matView));
	Math::Matrix4 matProj = mCamera->GetProjectionMatrix();

	TransformData data;
	data.wvp = Transpose(matWV * matProj);
	mTransformBuffer.Update(data);

	TextureCache* tc = TextureCache::Get();
	tc->BindPS(renderObject.diffuseMapId, 0);
	renderObject.meshBuffer.Render();
}

void BillBoardEffect::SetCamera(const Camera& camera)
{
	mCamera = &camera;
}
