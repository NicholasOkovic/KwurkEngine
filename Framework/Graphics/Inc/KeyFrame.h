#pragma once

#include "Common.h"

namespace KwurkEngine::Graphics
{
	template<class T>
	struct KeyFrame
	{
		KeyFrame() = default;
		KeyFrame(const T& k, float t)
			: key(k)
			, time(t)
		{

		}

		T key = T();
		float time = 0.0f;
	};

	template<class T>
	using KeyFrames = std::vector<KeyFrame<T>>;

	using AnimationCallBack = std::function<void()>;

	using PositionKeys = KeyFrames<Math::Vector3>;
	using RotationKeys = KeyFrames<Math::Quaternion>;
	using ScaleKeys = KeyFrames<Math::Vector3>;
	using EventKeys = KeyFrames<AnimationCallBack>;

}