#pragma once
#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"
#include "DirectionalLight.h"
#include "Material.h"

namespace KwurkEngine::Graphics
{
	class Camera;
	class RenderObject;



	class StandardEffect final
	{
	public:
		void Initialize(const std::filesystem::path & path);
		void Terminate();

		void Begin();
		void End();

		void Render(const RenderObject& renderObjects);

		void SetCamera(const Camera& camera);
		void SetDirectionalLight(const DirectionalLight& directionalLight);

		void DebugUI();

	private:
		struct TransformData
		{
			Math::Matrix4 wvp;
			Math::Matrix4 world;
			Math::Vector3 viewPosition;
			float padding = 0.0f;

		};
		
		struct SettingsData
		{
			int useDiffuseMap = 1;
			int useNormalMap = 1;
			int useSpecMap = 1;
			int useBumpMap = 1;
			float bumpWeight = 0.1f;
			float padding[3] = { 0.0f };
		};

		using TransformBuffer = TypedConstantBuffer<TransformData>;
		using LightBuffer = TypedConstantBuffer<DirectionalLight>;
		using MaterialBuffer = TypedConstantBuffer<Material>;
		using SettingsBuffer = TypedConstantBuffer<SettingsData>;

		TransformBuffer mTransformBuffer;
		LightBuffer mLightBuffer;
		MaterialBuffer mMaterialBuffer;
		SettingsBuffer mSettingsBuffer;

		VertexShader mVertexShader;
		PixelShader mPixelShader;
		Sampler mSampler;

		SettingsData mSettingsData;
		const Camera* mCamera = nullptr;
		const DirectionalLight* mDirectionalLight = nullptr;
	};
	
}
