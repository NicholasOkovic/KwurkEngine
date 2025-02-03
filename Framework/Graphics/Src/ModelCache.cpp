#include "Precompiled.h"
#include "ModelCache.h"

#include "ModelIO.h"

using namespace KwurkEngine;
using namespace KwurkEngine::Graphics;

namespace
{
	std::unique_ptr<ModelCache> sModelCache;
}


void ModelCache::StaticInitialize()
{
	ASSERT(sModelCache == nullptr, "ModelCache: is already initialized");
	sModelCache = std::make_unique<ModelCache>();
}

void ModelCache::StaticTerminate()
{
	sModelCache.reset();
}

ModelCache* ModelCache::Get()
{
	ASSERT(sModelCache != nullptr, "ModelCAche: was not initialized");
	return sModelCache.get();
}

ModelId ModelCache::GetModelId(const std::filesystem::path& filePath)
{
	return std::filesystem::hash_value(filePath);
}

ModelId ModelCache::LoadModel(const std::filesystem::path& filePath)
{
	const ModelId modelId = GetModelId(filePath);
	auto [iter, sucess] = mInventory.insert({ modelId, nullptr });
	if (sucess)
	{
		auto& modelPtr = iter->second;
		modelPtr = std::make_unique<Model>();
		ModelIO::LoadModel(filePath, *modelPtr);
		ModelIO::LoadMaterial(filePath, *modelPtr);
		ModelIO::LoadSkeleton(filePath, *modelPtr);
		ModelIO::LoadAnimations(filePath, *modelPtr);
	}
	return modelId;
}

void ModelCache::AddAnimation(ModelId id, const std::filesystem::path& filePath)
{
	auto model = mInventory.find(id);
	ASSERT(model != mInventory.end(), "ModelCache: need to load the model first");
	ModelIO::LoadAnimations(filePath, *model->second);
}

const Model* ModelCache::GetModel(ModelId id)
{
	auto model = mInventory.find(id);
	if (model != mInventory.end())
	{
		return model->second.get();
	}
	return nullptr;
}
