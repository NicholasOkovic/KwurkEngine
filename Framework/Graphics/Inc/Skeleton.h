#pragma once

#include "Bone.h"

namespace KwurkEngine::Graphics
{
	struct Skeleton
	{
		Bone* root = nullptr;
		std::vector<std::unique_ptr<Bone>> bones;
	};
}