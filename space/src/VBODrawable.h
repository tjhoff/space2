#pragma once
#include "MeshObject.h"
#include "Shader.h"
#include <string>

#define MESHDIR "meshes/"

#define SHADIR "shaders/"

#define MESH_SUFFIX ".obj"

#define FRAGMENT_SUFFIX ".fs"

#define VERTEX_SUFFIX ".vs"

class VBODrawable{

	public:
		VBODrawable(std::string meshname, std::string shadername);
		void draw();
	private:
		Shader * s;
		MeshObject * m;
};
