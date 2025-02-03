#pragma once

#include "KeyFrame.h"
#include "Transform.h"

namespace KwurkEngine::Graphics
{
	class Animation
	{
	public:
		Transform GetTranform(float time) const;
		float GetDuration() const;


	private:
		Math::Vector3 GetPosition(float time) const;
		Math::Quaternion GetRotation(float time) const;
		Math::Vector3 GetScale(float time) const;

		friend class AnimationBuilder;
		friend class AnimationIO;

		PositionKeys mPositionKeys;
		RotationKeys mRotationKeys;
		ScaleKeys mScaleKeys;

		//using KeyFrame = std::vector<KeyFrames>;
		//KeyFrame mKeyFrames;
		float mDuration;

	};


}