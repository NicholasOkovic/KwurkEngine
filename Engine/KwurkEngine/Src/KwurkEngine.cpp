#include "Precompiled.h"

#include "KwurkEngine.h"

KwurkEngine::App& KwurkEngine::MainApp()
{
	static KwurkEngine::App sAPP;
	return sAPP;
}
