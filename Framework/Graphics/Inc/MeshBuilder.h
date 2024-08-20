#pragma once

#include "MeshTypes.h"

namespace KwurkEngine::Graphics
{
	class Meshbuilder
	{
	public:
		//cube
		static MeshPC CreateCubePC(float size);

		//rectangle
		static MeshPC CreateRectPC(float width, float length, float height);

		//plane
		static MeshPC CreatePlanePC(int numRows, int numCols, float spacing);

		//Cylinder
		static MeshPC CreateCylinderPC(int slices, int rings);

		//Sphere
		static MeshPC CreateSpherePC(int slices, int rings, float radius);
	};
}