#pragma once

#include "Camera.h"
#include "ConstantBuffer.h"
#include "DirectionalLight.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "RenderTarget.h"


namespace KwurkEngine::Graphics
{
	class RenderObject;
	class RenderGroup;

	class ShadowEffect
	{
	public:
		enum class Type
		{
			None,
			Stippling,
			CrossHatching
		};

		void Initialize(const std::filesystem::path& path);
		void Terminate();

		void Begin();
		void End();

		void Render(const RenderObject& renderObject);
		void Render(const RenderGroup& renderGroup);

		void DebugUI();

		void SetDirectionalLight(const DirectionalLight& directionalLight);
		void SetFocus(const Math::Vector3& focusPoint);
		void SetSize(float size);
		void SetType(Type type);																////
		void SetTexture(const Texture* texture, uint32_t slot = 0);

		const Camera& GetLightCamera() const;
		const Texture& GetDepthMap() const;

	private:
		void UpdateLightCamera();

		struct TransformData
		{
			Math::Matrix4 wvp;
			int type;
			float param0 = 0.0f;
			float param1 = 0.0f;
			float param2 = 0.0f;
		};

		using TransformBuffer = TypedConstantBuffer<TransformData>;
		TransformBuffer mTransformBuffer;

		Type mType;
		std::array<const Texture*, 4> mTextures;

		VertexShader mVertexShader;
		PixelShader mPixelShader;

		Camera mLightCamera;
		RenderTarget mDepthMapRenderTarget;

		const DirectionalLight* mDirectionalLight = nullptr;
		Math::Vector3 mFocusPoint = Math::Vector3::Zero;
		float mSize = 100.0f;
	};


}


