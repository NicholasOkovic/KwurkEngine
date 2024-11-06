#include "Precompiled.h"
#include "RenderObject.h"
#include "Model.h"

using namespace KwurkEngine;
using namespace KwurkEngine::Graphics;

void RenderObject::Terminate()
{
	meshBuffer.Terminate();
}

void KwurkEngine::Graphics::RenderGroup::Initialize(const Model& model)
{
	for (const Model::MeshData& meshData : model.meshData)
	{
		RenderObject& renderObject = renderObjects.emplace_back();
		renderObject.meshBuffer.Initialize(meshData.mesh);
	}
}

void RenderGroup::Terminate()
{
	for (RenderObject& renderObject : renderObjects)
	{
		renderObject.Terminate();
	}
}

