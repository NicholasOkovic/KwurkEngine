#pragma once
#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"

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

		void DebugUI();

	private:
		struct TransformData
		{
			Math::Matrix4 wvp;
		};

		//light
		//mat
		//settings

		using TransformBuffer = TypedConstantBuffer<TransformData>;
		TransformBuffer mTransformBuffer;

		ConstantBuffer mConstantBuffer;
		VertexShader mVertexShader;
		PixelShader mPixelShader;
		Sampler mSampler;

		const Camera* mCamera = nullptr;
	};
	
}
