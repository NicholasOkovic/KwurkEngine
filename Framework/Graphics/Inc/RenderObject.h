#pragma once

#include "MeshBuffer.h"
#include "Transform.h"
#include "TextureCache.h"

namespace KwurkEngine::Graphics
{

	class RenderObject
	{
	public:
		void Terminate();

		Transform transform;
		MeshBuffer meshBuffer;
		TextureId diffuseTextureId;
	};
}

