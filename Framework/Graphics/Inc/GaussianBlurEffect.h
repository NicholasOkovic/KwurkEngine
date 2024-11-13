#pragma once

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"
#include "RenderTarget.h"


namespace KwurkEngine::Graphics
{
	class RenderObject;

	class GaussianBlurEffect
	{
	public:
		void Inittialize();
		void Terminate();

		void Begin();
		void End();

		void Render(const RenderObject& renderObject);

		void DebugUI();

		void SetSourceTexture(const Texture& texture);

		const Texture& GetHorizontalBlurTexture() const;
		const Texture& GetVerticalBlurTexture() const;
		const Texture& GetResultTexture() const;

	private:
		struct SettingData
		{
			float screenWidth = 0.0f;
			float screenHeight = 0.0f;
			float multiplier = 0.0f;
			float padding = 0.0f;
		};

		using SettingsBuffer = TypedConstantBuffer<SettingData>;
		SettingsBuffer mSettingsBuffer;

		RenderTarget mHorizontalBlurRenderTarget;
		RenderTarget mVerticalBlurRenderTarget;

		VertexShader mVertexShader;
		PixelShader mHorizontalBlurPixelShader;
		PixelShader mVerticalBlurPixelShader;

		Sampler mSampler;

		const Texture* mSourceTexture = nullptr;

		int mBluriterations = 10;
		float mBlurSaturation = 1.0f;
	};


}