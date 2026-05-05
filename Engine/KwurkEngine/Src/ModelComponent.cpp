#include "Precompiled.h"
#include "ModelComponent.h"
#include "SaveUtil.h"

using namespace KwurkEngine;

void ModelComponent::Initialize()
{
	Graphics::ModelCache* mm = Graphics::ModelCache::Get();
	mModelId = mm->GetModelId(mFileName);
	if (mm->GetModel(mModelId) == nullptr)
	{
		mModelId = mm->LoadModel(mFileName);
		for (const std::string& animation : mAnimations)
		{
			mm->AddAnimation(mModelId, animation);
		}
	}

	ASSERT(mm->GetModel(mModelId) != nullptr, "ModelComponent: failed to load model %s", mFileName.c_str());
	RenderObjectComponent::Initialize();

}

void ModelComponent::Terminate()
{
	RenderObjectComponent::Terminate();
}

void ModelComponent::Deserialize(const rapidjson::Value& value)
{
	RenderObjectComponent::Deserialize(value);

	SaveUtil::ReadString("FileName", mFileName, value);
	SaveUtil::ReadStringArray("Animations", mAnimations, value);
}

Graphics::ModelId ModelComponent::GetModelId() const
{
	return mModelId;
}

const Graphics::Model& ModelComponent::GetModel() const
{
	return *Graphics::ModelCache::Get()->GetModel(mModelId);		/////model manager
}
