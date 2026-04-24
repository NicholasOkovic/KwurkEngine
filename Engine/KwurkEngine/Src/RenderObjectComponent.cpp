#include "Precompiled.h"
#include "RenderObjectComponent.h"
#include "SaveUtil.h"
#include "GameWorld.h"
#include "RenderService.h"

using namespace KwurkEngine;

void RenderObjectComponent::Initialize()
{	 
	RenderService* renderService = GetOwner().GetWorld().GetService<RenderService>();
	if (renderService != nullptr)
	{
		renderService->Register(this);
	}
}	 
	 
void RenderObjectComponent::Terminate()
{	 
	RenderService* renderService = GetOwner().GetWorld().GetService<RenderService>();
	if (renderService != nullptr)
	{
		renderService->UnRegister(this);
	}
}	 
	 
void RenderObjectComponent::Deserialize(const rapidjson::Value& value)
{	 
	SaveUtil::ReadBool("CanCastShadow", mCastShadow, value);
}	 
	 
bool RenderObjectComponent::CanCastShadow() const
{
	return mCastShadow;
}
