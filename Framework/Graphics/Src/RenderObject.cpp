#include "Precompiled.h"
#include "RenderObject.h"

using namespace KwurkEngine;
using namespace KwurkEngine::Graphics;

void RenderObject::Terminate()
{
	meshBuffer.Terminate();
}
