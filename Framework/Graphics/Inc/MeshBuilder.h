#pragma once

#include "MeshTypes.h"

namespace KwurkEngine::Graphics
{
	class MeshBuilder
	{
	public:
		//cube
		static MeshPC CreateCubePC(float size);
		static MeshPX CreateCubePX(float size);
		static Mesh CreateCube(float size);

		//skyboxPX
		static MeshPX CreateSkyBoxPX(float size);
		static MeshPX CreateSkySpherePX(int slices, int rings, float radius);

		//rectangle
		static MeshPC CreateRectPC(float width, float length, float height);

		//plane
		static MeshPC CreatePlanePC(int numRows, int numCols, float spacing);
		static MeshPX CreatePlanePX(int numRows, int numCols, float spacing);
		static Mesh CreateGroundPlane(int numRows, int numCols, float spacing);

		//Cylinder
		static MeshPC CreateCylinderPC(int slices, int rings);

		//Sphere
		static MeshPC CreateSpherePC(int slices, int rings, float radius);
		static MeshPX CreateSpherePX(int slices, int rings, float radius);
		static Mesh CreateSphere(int slices, int rings, float radius);

		//Screen quad
		static MeshPX CreateScreenQuad();

		//sprite quad
		static MeshPX CreateSpriteQuad(float width, float height);

	};
}