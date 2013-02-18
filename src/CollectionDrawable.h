#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "VBOBase.h"
#include "Vec2.h"

class CollectionDrawable{
	public:
		CollectionDrawable();
		CollectionDrawable(unsigned int program);
		void draw();
		
	
	private:
		void generateField();
		void setData();
		std::vector<vertex> vertices;
		std::vector<texcoord> texcoords;
		std::vector<unsigned int> elements;
		
		unsigned int program;
		unsigned int uniform_tex;
		unsigned int vbo_texcoords;
		unsigned int vbo_vertices;
		unsigned int ibo_elements;
		unsigned int att_texcoords;
		unsigned int att_vertex;
		
};
