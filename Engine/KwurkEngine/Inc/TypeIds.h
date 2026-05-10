#pragma once

namespace KwurkEngine
{
	enum class ComponentId
	{
		Invalid,			//default value
		Transform,		//Transform component for location data
		Camera,			//The camera for viewing
		FPSCamera,		//move the camera component with fps controls
		Mesh,			//add a mesh shape on a game object
		Model,			// adds a model to the game object render
		Animator,		// adds an animation controller to the game object
		RigidBody,		//adds a physic object to the gaem object
		SoundEffect,	//addsa a sound effect to an object
		SoundBank,		// adds a group of sounds to an object
		Count,			// last value, can be used to chain custom components
	};

	enum class ServiceId
	{
		Invalid,			//default value
		Camera,			//manages the camera
		Render,			//renders renderobject in the world
		Physics,		//registers aand monitors physics objects
		Count,			// last value, can be used to chain custom components
	};

}



#define SET_TYPE_ID(id)\
	static uint32_t StaticGetTypeId() {return static_cast<uint32_t>(id); }\
	uint32_t GetTypedId() const override { return StaticGetTypeId(); }
