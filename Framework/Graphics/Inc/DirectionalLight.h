#pragma once


#include "Color.h"

namespace KwurkEngine::Graphics
{
	struct DirectionalLight
	{
		Color ambient = Colors::White; //light without light contact
		Color diffuse = Colors::White; //base ligth color
		Color specular = Colors::White; //highlight light color
		Math::Vector3 direction = Math::Vector3::ZAxis;
		float padding = 0.0f;
	};
}