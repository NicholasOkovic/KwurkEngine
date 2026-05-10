#pragma once
#include "CustomTypeIds.h"
#include "KwurkEngine/Inc/KwurkEngine.h"


class CustomDebugDrawComponent : public KwurkEngine::Component
{
public:
	SET_TYPE_ID(CustomComponentId::CustomDebugDraw);

	void Initialize() override;
	void Terminate() override;
	void DebugUI() override;
	void Deserialize(const rapidjson::Value& value) override;

	void AddDebugDraw() const;

private:

	const KwurkEngine::TransformComponent* mTransformComponent = nullptr;
	KwurkEngine::Math::Vector3 mPosition = KwurkEngine::Math::Vector3::Zero;
	KwurkEngine::Color mColor = KwurkEngine::Colors::White;

	uint32_t mSlices = 0;
	uint32_t mRings = 0;
	float mRadius = 0;

};



