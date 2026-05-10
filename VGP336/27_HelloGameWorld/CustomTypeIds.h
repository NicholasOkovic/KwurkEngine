#pragma once
#include "KwurkEngine/Inc/TypeIds.h"

enum class CustomComponentId
{
	CustomDebugDraw = static_cast<int>(KwurkEngine::ComponentId::Count)
};

enum class CustomServiceId
{
	CustomDebugDrawDisplay = static_cast<int>(KwurkEngine::ServiceId::Count)
};
