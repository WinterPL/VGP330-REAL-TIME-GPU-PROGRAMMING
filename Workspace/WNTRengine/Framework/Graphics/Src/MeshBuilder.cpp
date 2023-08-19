#include "Precompiled.h"
#include "MeshBuilder.h"

using namespace WNTRengine;
using namespace WNTRengine::Graphics;

namespace
{
	Color GetNextColor(int& index)
	{
		constexpr Color colorTable[] = {
			Colors::DarkBlue,
			Colors::Aqua,
			Colors::LightGreen,
			Colors::PapayaWhip,
			Colors::Silver,
			Colors::Orange,
			Colors::Green,
			Colors::Red
		};

		index = (index + 1) % std::size(colorTable);
		return colorTable[index];
	}
	void CreateCubeIndices(std::vector<uint32_t>& indices)
	{
		indices = {
			//front
			0, 1, 2,
			0, 2, 3,

			//back
			7, 6, 5,
			7, 5, 4,

			//right
			3, 2, 6,
			3, 6, 7,

			//left
			0, 5, 1,
			0, 4, 5,

			//top
			1, 5, 6,
			1, 6, 2,

			//bottom
			0, 3, 7,
			0, 7, 4
		};
		
	}
	void CreateSkyBoxCubeIndices(std::vector<uint32_t>& indices)
	{
		indices = {
			//front
			0, 2, 1,
			0, 3, 2,

			//back
			7, 5, 6,
			7, 4, 5,

			//right
			3, 6, 2,
			3, 7, 6,

			//left
			0, 1, 5,
			0, 5, 4,

			//top
			1, 6, 5,
			1, 2, 6,

			//bottom
			0, 7, 3,
			0, 4, 7
		};
	}
	void CreatePlaneIndices(std::vector<uint32_t>& indices, int numRows, int numColumns)
	{
		for (int r = 0; r < numRows; ++r)
		{
			for (int c = 0; c < numColumns; ++c)
			{
				int i = (r * (numColumns + 1)) + c;

				//triangle 1
				indices.push_back(i);
				indices.push_back(i + numColumns + 2);
				indices.push_back(i + 1);

				//triangle 2
				indices.push_back(i);
				indices.push_back(i + numColumns + 1);
				indices.push_back(i + numColumns + 2);
			}
		}
	}

	void CreateCapIndices(std::vector<uint32_t>& indices, int slices, int topIndex, int bottomIndex)
	{
		for (int s = 0; s < slices; ++s)
		{
			//bottom triangle
			indices.push_back(s);
			indices.push_back(s + 1);
			indices.push_back(bottomIndex);

			//top triangle
			int topRowStartIndex = topIndex - slices - 1 + s;
			indices.push_back(topIndex);
			indices.push_back(topRowStartIndex + 1);
			indices.push_back(topRowStartIndex);
		}

	}
}

//cubes
MeshPC MeshBuilder::CreateCubePC(float size, const Color& color)
{
	MeshPC mesh;

	const float hs = size * 0.5f;
	//front
	mesh.vertices.push_back({ { -hs, -hs, -hs }, color }); //0
	mesh.vertices.push_back({ { -hs, hs, -hs }, color }); //1
	mesh.vertices.push_back({ { hs, hs, -hs }, color }); //2
	mesh.vertices.push_back({ { hs, -hs, -hs }, color }); //3

	//back
	mesh.vertices.push_back({ { -hs, -hs, hs }, color }); //4
	mesh.vertices.push_back({ { -hs, hs, hs }, color }); //5
	mesh.vertices.push_back({ { hs, hs, hs }, color }); //6
	mesh.vertices.push_back({ { hs, -hs, hs }, color }); //7

	CreateCubeIndices(mesh.indices);


	return mesh;
}
MeshPX MeshBuilder::CreateCubePX(float size)
{
	MeshPX mesh;

	const float hs = size * 0.5f;
	//front
	mesh.vertices.push_back({ { -hs, -hs, -hs }, {0.25f, 0.66f} }); //0
	mesh.vertices.push_back({ { -hs, hs, -hs },  {0.25f, 0.33f} }); //1
	mesh.vertices.push_back({ { hs, hs, -hs },   {0.5f, 0.33f} }); //2
	mesh.vertices.push_back({ { hs, -hs, -hs },  {0.5f, 0.66f} }); //3

	//back
	mesh.vertices.push_back({ { -hs, -hs, hs },  {0.25f, 1.0f} }); //4
	mesh.vertices.push_back({ { -hs, hs, hs },   {0.0f, 0.33f} }); //5
	mesh.vertices.push_back({ { hs, hs, hs },    {0.5f, 0.0f}  }); //6
	mesh.vertices.push_back({ { hs, -hs, hs },   {0.5f, 1.0f}  }); //7

	CreateCubeIndices(mesh.indices);
	return mesh;
}


MeshPX MeshBuilder::CreateSkyBox(float size) {
	MeshPX mesh;

	const float hs = size * 0.5f;
	const float oneThird = 1.f / 3.f;
	const float twoThird = 2.f / 3.f;
	//front
	mesh.vertices.push_back({ { size,  size, -size},{0.5f,oneThird}});
	mesh.vertices.push_back({ {-size, -size, -size},{0.25f,twoThird}});
	mesh.vertices.push_back({ { size, -size, -size},{0.5f,twoThird}});

	mesh.vertices.push_back({ { size,  size, -size},{0.5f,oneThird} });
	mesh.vertices.push_back({ {-size,  size, -size},{0.25f,oneThird} });
	mesh.vertices.push_back({ {-size, -size, -size},{0.5f,twoThird} });
	//Back
	mesh.vertices.push_back({ {-size,  size, size},{1.0f,oneThird} });
	mesh.vertices.push_back({ { size, -size, size},{0.75f,twoThird} });
	mesh.vertices.push_back({ {-size, -size, size},{1.0f,twoThird} });

	mesh.vertices.push_back({ {-size,  size, size},{1.0f,oneThird} });
	mesh.vertices.push_back({ { size,  size, size},{0.75f,oneThird} });
	mesh.vertices.push_back({ { size, -size, size},{1.0f,twoThird} });
	//Right
	mesh.vertices.push_back({ { size,  size, size},{0.75f,oneThird} });
	mesh.vertices.push_back({ { size, -size,-size},{0.5f,twoThird} });
	mesh.vertices.push_back({ {-size, -size, size},{0.75f,twoThird} });

	mesh.vertices.push_back({ { size,  size, size},{0.75f,oneThird} });
	mesh.vertices.push_back({ { size,  size,-size},{0.5f,oneThird} });
	mesh.vertices.push_back({ { size, -size,-size},{0.5f,twoThird} });
	//Left
	mesh.vertices.push_back({ {-size,  size,-size},{0.25f,oneThird} });
	mesh.vertices.push_back({ {-size, -size, size},{0.0f,twoThird} });
	mesh.vertices.push_back({ {-size, -size,-size},{0.25f,twoThird} });

	mesh.vertices.push_back({ {-size,  size,-size},{0.25f,oneThird} });
	mesh.vertices.push_back({ {-size,  size, size},{0.0f,oneThird} });
	mesh.vertices.push_back({ {-size, -size, size},{0.0f,twoThird} });
	//Top
	mesh.vertices.push_back({ { size,  size, size},{0.5f,0.0f} });
	mesh.vertices.push_back({ {-size,  size,-size},{0.25f,oneThird} });
	mesh.vertices.push_back({ { size,  size,-size},{0.5f,oneThird} });

	mesh.vertices.push_back({ { size,  size, size},{0.5f,0.0f} });
	mesh.vertices.push_back({ {-size,  size, size},{0.25f,oneThird} });
	mesh.vertices.push_back({ {-size,  size,-size},{0.5f,oneThird} });

	//Buttom
	mesh.vertices.push_back({ { size, -size,-size},{0.5f,twoThird} });
	mesh.vertices.push_back({ {-size, -size, size},{0.25f,1.0f} });
	mesh.vertices.push_back({ { size, -size, size},{0.5f,1.0f} });

	mesh.vertices.push_back({ { size, -size,-size},{0.5f,twoThird} });
	mesh.vertices.push_back({ {-size, -size,-size},{0.25f,twoThird} });
	mesh.vertices.push_back({ {-size, -size, size},{0.5f,1.0f} });
	
	int i = 0;
	for (const auto& Vertex : mesh.vertices) {
		mesh.indices.push_back(i);
		++i;
	}
	return mesh;
}

MeshPX MeshBuilder::CreateSkyBoxSphere(int slices, int rings, float radius)
{
	MeshPX mesh;

	float vertRotation = (WNTRmath::Constants::Pi / static_cast<float>(rings - 1));
	float horzRotation = (WNTRmath::Constants::TwoPi / static_cast<float>(slices));
	float uStep = 1.0f / static_cast<float>(slices);
	float vStep = 1.0f / static_cast<float>(rings);
	for (int r = 0; r <= rings; r++)
	{
		float ring = static_cast<float>(r);
		float phi = ring * vertRotation;
		for (int s = 0; s <= slices; s++)
		{
			float slice = static_cast<float>(s);
			float rotation = slice * horzRotation;

			float u = 1.0f - (uStep * slice);
			float v = vStep * ring;
			mesh.vertices.push_back({ {
				radius * cos(rotation) * sin(phi),
				radius * cos(phi),
				radius * sin(rotation) * sin(phi)
			},
				{u,v} });
		}
	}
	CreatePlaneIndices(mesh.indices, rings, slices);
	return mesh;
}

//sphere
MeshPC MeshBuilder::CreateSpherePC(int slices, int rings, float radius)
{
	MeshPC mesh;
	int index = rand() % 100;

	float vertRotation = (WNTRmath::Constants::Pi / static_cast<float>(rings - 1));
	float horzRotation = (WNTRmath::Constants::TwoPi / static_cast<float>(slices));
	for (int r = 0; r <= rings; r++)
	{
		float ring = static_cast<float>(r);
		float phi = ring * vertRotation;
		for (int s = 0; s <= slices; s++)
		{
			float slice = static_cast<float>(s);
			float rotation = slice * horzRotation;

			mesh.vertices.push_back({ {
				radius * sin(rotation) * sin(phi),
				radius * cos(phi),
				radius * cos(rotation) * sin(phi)
			},
			GetNextColor(index) });
		}

	}
	CreatePlaneIndices(mesh.indices, rings, slices);

	return mesh;
}
MeshPX MeshBuilder::CreateSpherePX(int slices, int rings, float radius)
{
	MeshPX mesh;

	float vertRotation = (WNTRmath::Constants::Pi / static_cast<float>(rings - 1));
	float horzRotation = (WNTRmath::Constants::TwoPi / static_cast<float>(slices));
	float uStep = 1.0f / static_cast<float>(slices);
	float vStep = 1.0f / static_cast<float>(rings);
	for (int r = 0; r <= rings; r++)
	{
		float ring = static_cast<float>(r);
		float phi = ring * vertRotation;
		for (int s = 0; s <= slices; s++)
		{
			float slice = static_cast<float>(s);
			float rotation = slice * horzRotation;

			float u = 1.0f - (uStep * slice);
			float v = vStep * ring;
			mesh.vertices.push_back({ {
				radius * sin(rotation) * sin(phi),
				radius * cos(phi),
				radius * cos(rotation) * sin(phi)
			},
				{u,v} });
		}

	}
	CreatePlaneIndices(mesh.indices, rings, slices);
	return mesh;
}
Mesh MeshBuilder::CreateSphere(int slices, int rings, float radius)
{
	Mesh mesh;

	float vertRotation = (WNTRmath::Constants::Pi / static_cast<float>(rings - 1));
	float horzRotation = (WNTRmath::Constants::TwoPi / static_cast<float>(slices));
	float uStep = 1.0f / static_cast<float>(slices);
	float vStep = 1.0f / static_cast<float>(rings);
	for (int r = 0; r <= rings; r++)
	{
		float ring = static_cast<float>(r);
		float phi = ring * vertRotation;
		for (int s = 0; s <= slices; s++)
		{
			float slice = static_cast<float>(s);
			float rotation = slice * horzRotation;

			float u = 1.0f - (uStep * slice);
			float v = vStep * ring;

			float x = radius * sin(rotation) * sin(phi);
			float y = radius * cos(phi);
			float z = radius * cos(rotation) * sin(phi);
			const WNTRmath::Vector3 pos = { x,y,z };
			const WNTRmath::Vector3 norm = WNTRmath::Normalize(pos);
			const WNTRmath::Vector3 tan = WNTRmath::Normalize({ -z,0.0f,x });

			mesh.vertices.push_back({ pos,norm,tan,{u,v} });
		}

	}
	CreatePlaneIndices(mesh.indices, rings, slices);
	return mesh;
}


//rect
MeshPC MeshBuilder::CreateRectPC(float width, float height, float depth)
{
	MeshPC mesh;
	int index = rand() % 100;
	const float hw = width * 0.5f; // x
	const float hh = height * 0.5f;// y
	const float hd = depth * 0.5f; // z

	//front
	mesh.vertices.push_back({ { -hw, -hh, -hd }, GetNextColor(index) }); //0
	mesh.vertices.push_back({ { -hw, hh, -hd }, GetNextColor(index) }); //1
	mesh.vertices.push_back({ { hw, hh, -hd }, GetNextColor(index) }); //2
	mesh.vertices.push_back({ { hw, -hh, -hd }, GetNextColor(index) }); //3

	//back
	mesh.vertices.push_back({ { -hw, -hh, hd }, GetNextColor(index) }); //4
	mesh.vertices.push_back({ { -hw, hh, hd }, GetNextColor(index) }); //5
	mesh.vertices.push_back({ { hw, hh, hd }, GetNextColor(index) }); //6
	mesh.vertices.push_back({ { hw, -hh, hd }, GetNextColor(index) }); //7

	CreateCubeIndices(mesh.indices);

	return mesh;
}
MeshPX MeshBuilder::CreateRectPX(float width, float height, float depth)
{
	MeshPX mesh;
	const float hw = width * 0.5f; // x
	const float hh = height * 0.5f;// y
	const float hd = depth * 0.5f; // z

	//front
	mesh.vertices.push_back({ { -hw, -hh, -hd }, {0.25f, 0.66f} }); //0
	mesh.vertices.push_back({ { -hw, hh, -hd },  {0.25f, 0.33f} }); //1
	mesh.vertices.push_back({ { hw, hh, -hd },   {0.5f, 0.33f} }); //2
	mesh.vertices.push_back({ { hw, -hh, -hd },  {0.5f, 0.66f} }); //3

	//back
	mesh.vertices.push_back({ { -hw, -hh, hd },  {0.25f, 1.0f} }); //4
	mesh.vertices.push_back({ { -hw, hh, hd },   {0.0f, 0.33f} }); //5
	mesh.vertices.push_back({ { hw, hh, hd },    {0.5f, 0.0f} }); //6
	mesh.vertices.push_back({ { hw, -hh, hd },   {0.5f, 1.0f} }); //7

	CreateCubeIndices(mesh.indices);
	return mesh;
}

//plane
MeshPC MeshBuilder::CreatePlanePC(int numRows, int numCols, int spacing)
{
	MeshPC mesh;
	int index = rand() % 100;

	const float hpw = static_cast<float>(numCols) * spacing * 0.5f;
	const float hph = static_cast<float>(numRows) * spacing * 0.5f;

	float x = -hpw;
	float y = -hph;

	for (int r = 0; r <= numRows; r++)
	{
		for (int c = 0; c <= numCols; c++)
		{
			mesh.vertices.push_back({ {x,y,0.0f}, GetNextColor(index) });
			x += spacing;
		}
		x = -hpw;
		y += spacing;
	}

	CreatePlaneIndices(mesh.indices, numRows, numCols);

	return mesh;
}

Mesh MeshBuilder::CreateGroupPlane(int numRows, int numCols, float spacing)
{
	Mesh mesh;
	int index = rand() % 100;

	const float hpw = static_cast<float>(numCols) * spacing * 0.5f;
	const float hph = static_cast<float>(numRows) * spacing * 0.5f;
	float uInc = 1.0f / (float)(numCols);
	float vInc = 1.0f / (float)(numRows);

	float x = -hpw;
	float z = -hph;
	float u = 0.0f;
	float v = 1.0f;

	for (int r = 0; r <= numRows; ++r)
	{
		for (int c = 0; c <= numCols; ++c)
		{
			mesh.vertices.push_back({
				{x,0.0f,z},
				{0.0f,1.0f,0.0f},
				{0.0f,0.0f,1.0f},
				{u,v}});
			x += spacing;
			u += uInc;
		}
		u = 0.0f;
		v -= vInc;
		x = -hpw;
		z += spacing;
	}

	CreatePlaneIndices(mesh.indices, numRows, numCols);

	return mesh;
}

//cylinder
MeshPC MeshBuilder::CreateCylinderPC(int slices, int rings)
{
	MeshPC mesh;

	int index = rand() % 100;
	const float hh = static_cast<float>(rings) * 0.5f;

	for (int r = 0; r <= rings; ++r)
	{
		float ring = static_cast<float>(r);
		for (int s = 0; s <= slices; ++s)
		{
			float slice = static_cast<float>(s);
			float rotation = (slice / static_cast<float>(slices)) * WNTRmath::Constants::TwoPi;

			mesh.vertices.push_back({ {
					sin(rotation),
					ring - hh,
					-cos(rotation)},
					GetNextColor(index) });
		}
	}

	mesh.vertices.push_back({ { 0.0f, hh, 0.0f }, GetNextColor(index) });
	mesh.vertices.push_back({ { 0.0f, -hh, 0.0f }, GetNextColor(index) });

	CreatePlaneIndices(mesh.indices, rings, slices);
	CreateCapIndices(mesh.indices, slices, static_cast<int>(mesh.vertices.size() - 2), static_cast<int>(mesh.vertices.size() - 1));

	return mesh;
}

MeshPX MeshBuilder::CreateScreenQuad()
{
	MeshPX mesh;
	mesh.vertices.push_back({{ -1.0, -1.0, 0.0f }, { 0.0f, 1.0f }});
	mesh.vertices.push_back({{ -1.0,  1.0, 0.0f }, { 0.0f, 0.0f }});
	mesh.vertices.push_back({{  1.0,  1.0, 0.0f }, { 1.0f, 0.0f }});
	mesh.vertices.push_back({{  1.0, -1.0, 0.0f }, { 1.0f, 1.0f }});
	mesh.indices = { 0,1,2,0,2,3 };

	return mesh;
}