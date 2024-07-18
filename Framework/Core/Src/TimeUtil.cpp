#include "Precompiled.h"
#include "TimeUtil.h"


using namespace KwurkEngine;
using namespace KwurkEngine::Core;


float KwurkEngine::Core::TimeUtil::GetTime()
{
	//gives you the durations since the application started (runtime)
	static const auto startTime = std::chrono::high_resolution_clock::now();
	const auto currentTime = std::chrono::high_resolution_clock::now();
	const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
	return milliseconds / 1000.0f;
}

float KwurkEngine::Core::TimeUtil::GetDeltaTime()
{
	//gives you the durations since the application started (runtime)
	static auto lastCallTime = std::chrono::high_resolution_clock::now();
	const auto currentTime = std::chrono::high_resolution_clock::now();
	const auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastCallTime).count();
	lastCallTime = currentTime;
	return milliseconds / 1000.0f;
}
