#include "Precompiled.h"
#include "ShadowEffect.h"

#include "RenderObject.h"
#include "VertexTypes.h"

using namespace KwurkEngine;
using namespace KwurkEngine::Graphics;

const char* sTypeNames[] =
{
	"None",
	"Stippling",
	"CrossHatching"
};

void ShadowEffect::Initialize(const std::filesystem::path& path)
{

	mVertexShader.Initialize<Vertex>(path);
	mPixelShader.Initialize(path);
	mTransformBuffer.Initialize();
	mLightCamera.SetMode(Camera::ProjectionMode::Orthographic);
	mLightCamera.SetNearPlane(1.0f);
	mLightCamera.SetFarPlane(2000.0f);

	constexpr uint32_t depthMapResolution = 4096;
	mDepthMapRenderTarget.Initialize(depthMapResolution, depthMapResolution, Texture::Format::RGBA_U32);
}

void ShadowEffect::Terminate()
{
	mDepthMapRenderTarget.Terminate();
	mTransformBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
}

void ShadowEffect::Begin()
{
	UpdateLightCamera();
	mVertexShader.Bind();
	mPixelShader.Bind();
	TransformData data;

	mTransformBuffer.Update(data);
	mTransformBuffer.BindVS(0);
	
	mDepthMapRenderTarget.BeginRender();
}

void ShadowEffect::End()
{
	mDepthMapRenderTarget.EndRender();
}

void ShadowEffect::Render(const RenderObject& renderObject)
{
	const Math::Matrix4 matWorld = renderObject.transform.GetMatrix4();
	const Math::Matrix4 matView = mLightCamera.GetViewMatrix();
	const Math::Matrix4 matProj = mLightCamera.GetProjectionMatrix();

	TransformData data;
	data.wvp = Math::Transpose(matWorld * matView * matProj);

	data.type = static_cast<int>(mType);

	mTransformBuffer.Update(data);
	renderObject.meshBuffer.Render();
}

void ShadowEffect::Render(const RenderGroup& renderGroup)
{
	const Math::Matrix4 matWorld = renderGroup.transform.GetMatrix4();
	const Math::Matrix4 matView = mLightCamera.GetViewMatrix();
	const Math::Matrix4 matProj = mLightCamera.GetProjectionMatrix();

	TransformData data;
	data.wvp = Math::Transpose(matWorld * matView * matProj);

	data.type = static_cast<int>(mType);

	mTransformBuffer.Update(data);
	for (const RenderObject& renderObject : renderGroup.renderObjects)
	{
		renderObject.meshBuffer.Render();
	}
}

void ShadowEffect::DebugUI()
{
	if (ImGui::CollapsingHeader("ShadowEffect", ImGuiTreeNodeFlags_DefaultOpen))
	{

		ImGui::Text("DepthMap");
		ImGui::Image(
			mDepthMapRenderTarget.GetRawData(),
			{ 144, 144 },
			{ 0, 0 },
			{ 1, 1 },
			{ 1, 1, 1 ,1 },
			{ 1, 1, 1 ,1 });
		ImGui::DragFloat("Size##Shadow", &mSize, 1.0f, 1.0f, 1000.0f);

		////////create space
		int currentType = static_cast<int>(mType);
		if (ImGui::Combo("Type", &currentType, sTypeNames, std::size(sTypeNames)))
		{
			mType = static_cast<Type>(currentType);
		}

	}
}

void ShadowEffect::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	mDirectionalLight = &directionalLight;
}

void ShadowEffect::SetFocus(const Math::Vector3& focusPoint)
{
	mFocusPoint = focusPoint;
}

void ShadowEffect::SetSize(float size)
{
	mSize = size;
}

void ShadowEffect::SetType(Type type)
{
	mType = type;
}

void ShadowEffect::SetTexture(const Texture* texture, uint32_t slot)
{
	ASSERT(slot < mTextures.size(), "ShadowEffect: invalid slot index");
	mTextures[slot] = texture;
}

const Camera& ShadowEffect::GetLightCamera() const
{
	return mLightCamera;
}

const Texture& ShadowEffect::GetDepthMap() const
{
	return mDepthMapRenderTarget;
}

void ShadowEffect::UpdateLightCamera()
{
	ASSERT(mDirectionalLight != nullptr, "ShadowEffect: no light set");
	const Math::Vector3& direction = mDirectionalLight->direction;
	mLightCamera.SetDirection(direction);
	mLightCamera.SetPosition(mFocusPoint - (direction * 1000.0f));
	mLightCamera.SetSize(mSize, mSize);

}
