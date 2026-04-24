#pragma once

#include "GameObjectHandle.h"
#include "Component.h"

namespace KwurkEngine
{
	class GameWorld;

	class GameObject final
	{
	public:
		GameObject() = default;

		void Initialize();
		void Terminate();
		void Update(float deltaTime);
		void DebugUI();


		void SetName(std::string& name);
		const std::string& GetName() const;
		uint32_t GetId() const;
		const GameObjectHandle& GetHandle() const;

		GameWorld& GetWorld();
		const GameWorld& GetWorld() const;

		template<class ComponentType>
		ComponentType* AddComponent()
		{
			static_assert(std::is_base_of_v<Component, ComponentType>,
				"GameObject: componentType must be og type component");
			ASSERT(!mInitialized, " GameObject: can't add components when initialized");
			ASSERT(!HasA<ComponentType>(), "GameObject: already has a coomponent type added");
			ASSERT(ComponentType::StaticGetTypeId() != static_cast<uint32_t>(ComponentId::Invalid),
				"GameObject: component has invalid Id");

			auto& newComponent = mComponents.emplace_back(std::make_unique<ComponentType>());
			newComponent->mOwner = this;
			return static_cast<ComponentType*>(newComponent.get());
		}

		template<class ComponentType>
		bool HasA()
		{
			ASSERT(ComponentType::StaticGetTypeId() != static_cast<uint32_t>(ComponentId::Invalid),
				"GameObject: component has invalid Id");
			for (auto& component : mComponents)
			{
				if (component->GetTypedId() == ComponentType::StaticGetTypeId())
				{
					return true;
				}
			}
			return false;
		}

		template<class ComponentType>
		const ComponentType* GetComponent() const
		{
			ASSERT(ComponentType::StaticGetTypeId() != static_cast<uint32_t>(ComponentId::Invalid),
				"GameObject: component has invalid Id");
			for (auto& component : mComponents)
			{
				if (component->GetTypedId() == ComponentType::StaticGetTypeId())
				{
					return static_cast<ComponentType*>(component.get());
				}
			}
			return nullptr;
		}
		template<class ComponentType>
		ComponentType* GetComponent()
		{
			const GameObject* thisConst = static_cast<const GameObject*>(this);
			return const_cast<ComponentType*>(thisConst->GetComponent<ComponentType>());
		}


	private:
		friend class GameWorld;

		std::string mName = "EMPTY";
		bool mInitialized = false;
		uint32_t mId = 0;

		GameObjectHandle mHandle;
		GameWorld* mWorld = nullptr;

		using Components = std::vector<std::unique_ptr<Component>>;
		Components mComponents;
	};

}