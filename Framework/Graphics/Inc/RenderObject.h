#pragma once

#include "MeshBuffer.h"
#include "Transform.h"
#include "TextureCache.h"
#include "Material.h"

namespace KwurkEngine::Graphics
{
	struct Model;

	class RenderObject
	{
	public:
		void Terminate();

		Transform transform;
		MeshBuffer meshBuffer;

		Material material;
		TextureId diffuseMapId;
		TextureId normalMapId;
		TextureId specMapId;
		TextureId bumpMapId;
	};

	class RenderGroup
	{
	public:
		void Initialize(const Model& model);
		void Terminate();

		Transform transform;
		std::vector<RenderObject> renderObjects;
	};

}

