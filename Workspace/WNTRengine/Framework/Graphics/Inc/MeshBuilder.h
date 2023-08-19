#pragma once
#include "MeshTypes.h"	

namespace WNTRengine::Graphics
{
	class MeshBuilder
	{
	public:
		//cubes
		static MeshPC CreateCubePC(float size, const Color& color);
		static MeshPX CreateCubePX(float size);

		static MeshPX CreateSkyBox(float size);
		static MeshPX CreateSkyBoxSphere(int slice,int rings, float radius);
		//sphere
		static MeshPC CreateSpherePC(int slices, int rings, float radius);
		static MeshPX CreateSpherePX(int slices, int rings, float radius);
		static Mesh CreateSphere(int slices, int rings, float radius);
		//Rect
		static MeshPC CreateRectPC(float width, float height, float depth);
		static MeshPX CreateRectPX(float width, float height, float depth);
		//Plane
		static MeshPC CreatePlanePC(int numRows, int numCols, int spacing);
		static Mesh CreateGroupPlane(int numRows, int numCols, float spacing);
		//Cylinder
		static MeshPC CreateCylinderPC(int slices, int rings);

		//Screen Quad
		static MeshPX CreateScreenQuad();

	};
}