#pragma once

#include "ModelCache.h"

namespace KwurkEngine::Graphics::AnimationUtil
{
	using BoneTransforms = std::vector<Math::Matrix4>;

	void ComputeBoneTransforms(ModelId modelId, BoneTransforms& boneTransforms);
	void DrawSkeleton(ModelId modelId, const BoneTransforms& boneTransforms);

}
