#pragma once

#include "Service.h"

namespace KwurkEngine
{
	class CamerService;
	class RenderObjectComponent;
	class transformComponent;

	class RenderService : public Service
	{
	public:
		SET_TYPE_ID(ServiceId : Render);

		void Initialize() override;
		void Terminate() override;
		void Update(float deltaTime) override;
		void Render() override;
		void DebugUI() override;

		void Register(const RenderObjectComponent* renderComponent);
		void UnRegister(const RenderObjectComponent* renderComponent);
	private:
		const CameraService* mCameraService = nullptr;
		Graphics::DirectionalLight mDirectionalLight;
		Graphics::StandardEffect mStandardEffect;
		Graphics::ShadowEffect mShadowEffect;

		struct Entry
		{
			const RenderObjectComponent* renderComponent = nullptr;
			const TransformComponent* transformComponent = nullptr;
			Graphics::RenderGroup renderGroup;


		};
		using RenderEntries = std::vector<Entry>;
		RenderEntries mRenderEntries;

		float mFPS = 0.0f;

	};

}
