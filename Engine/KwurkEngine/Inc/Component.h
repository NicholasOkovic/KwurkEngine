#pragma once

#include "TypeIds.h"

namespace KwurkEngine
{
	class GameObject;

	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		Component(const Component&) = delete;
		Component(const Component&&) = delete;
		Component& operator=(const Component&) = delete;
		Component& operator=(const Component&&) = delete;

		virtual void Initialize() {}
		virtual void Terminate() {}
		virtual void Update(float deltaTime) {}
		virtual void DebugUI() {}

		//will add erad in data apply the object
		virtual void Deserialize(const rapidjson::Value& value){}
		//will write out data to a a jsoon document, which will be saved to a json file
		virtual void Serialize(rapidjson::Document& doc, rapidjson::Value& value, const rapidjson::Value& originalValue) {}

		virtual uint32_t GetTypedId() const = 0;
		
		GameObject& GetOwner() { return *mOwner; }
		const GameObject& GetOwner() const { return *mOwner; }
		 

	private:
		friend class GameObject;
		GameObject* mOwner = nullptr;


	};
}