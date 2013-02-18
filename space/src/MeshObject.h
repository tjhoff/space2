#pragma once
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <float.h>
#include "VBOBase.h"

class MeshObject{
	public:
		MeshObject();
		MeshObject(unsigned int program);
		MeshObject(const char *  filename, unsigned int program);
		void load(const char*  filename);
		void draw();
		
		vec3 getMaxBound();
		vec3 getMinBound();
	
	private:
		void setData();
		std::vector<vertex> vertices;
		std::vector<vertex> normals;
		std::vector<texcoord> texcoords;
		std::vector<unsigned int> elements;
		
		vec3 max;
		vec3 min;
		
		unsigned int program;
		unsigned int vbo_vertices;
		unsigned int vbo_texcoords;
		unsigned int vbo_normals;
		unsigned int ibo_elements;
		unsigned int att_normal;
		unsigned int att_texcoord;
		unsigned int att_vertex;
		
		unsigned int uniform_tex;
		
};
