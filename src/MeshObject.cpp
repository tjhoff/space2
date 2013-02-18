#include "MeshObject.h"

using namespace std;

MeshObject::MeshObject(){
	program = 0;
}

MeshObject::MeshObject(unsigned int shader_program){
	program = shader_program;
	glGenBuffers(1, &vbo_vertices);
	glGenBuffers(1, &vbo_normals);
	glGenBuffers(1, &vbo_texcoords);
	glGenBuffers(1, &ibo_elements);
}

MeshObject::MeshObject(const char *  filename, unsigned int shader_program){

	program = shader_program;

	glGenBuffers(1, &vbo_vertices);
	glGenBuffers(1, &vbo_normals);
	glGenBuffers(1, &vbo_texcoords);
	glGenBuffers(1, &ibo_elements);
	load(filename);
}

vec3 MeshObject::getMinBound(){
	return min;
}

vec3 MeshObject::getMaxBound(){
	return max;
}

void MeshObject::load(const char * filename){
	
	printf("loading data\n");
	
	ifstream in(filename, ios::in);
	
	if (!in) {
		printf("Can't open %s\n", filename);
		return;
	}
	
	string line;
	
	vector<vertex> normal_temp_vector;
	vector<texcoord> tmp_texcoords;
	vector<vertex> tmp_vertices;
	
	int vx_index = 0;	
	
	while (getline(in, line)){
		
		if (line.substr(0,2) == "v "){
			// This is a vertex
			istringstream s(line.substr(2));
			vertex v;
			s>>v.x;s>>v.y;s>>v.z;
			tmp_vertices.push_back(v);
			
		}
		
		else if (line.substr(0,2) == "f "){
			// This is a face
			// -- if this happens after a normal, we're screwed ---
			// -- or a texcoord. HA HA HA, HA! --
			string l_copy = line.substr(2);
			unsigned int va, vb, vc, na, nb, nc, ta, tb, tc;
			
			sscanf(l_copy.c_str(), "%u/%u/%u %u/%u/%u %u/%u/%u", &va, &ta, &na, &vb,&tb, &nb, &vc, &tc, &nc);
			
			elements.push_back(vx_index);
			elements.push_back(vx_index+1);
			elements.push_back(vx_index+2);
			
			vx_index +=3;
			
			vertices.push_back(tmp_vertices[va-1]);
			vertices.push_back(tmp_vertices[vb-1]);
			vertices.push_back(tmp_vertices[vc-1]);
			normals.push_back(normal_temp_vector[na-1]);
			normals.push_back(normal_temp_vector[nb-1]);
			normals.push_back(normal_temp_vector[nc-1]);
			texcoords.push_back(tmp_texcoords[ta-1]);
			texcoords.push_back(tmp_texcoords[tb-1]);
			texcoords.push_back(tmp_texcoords[tc-1]);
			
		}
		
		if (line.substr(0,2) == "vt"){
			// This is a texture coordinate
			istringstream s(line.substr(2));
			texcoord t;
			s>>t.s;s>>t.t;
			tmp_texcoords.push_back(t);
			
		}
		
		else if (line.substr(0,2) == "vn"){
			// This is a normal
			istringstream s(line.substr(2));
			vec3 v;
			s>>v.x;s>>v.y;s>>v.z;
			
			v = v.normalize();
			
			vertex vx;
			vx.x = v.x;
			vx.y = v.y;
			vx.z = v.z;
			
			normal_temp_vector.push_back(vx);
			
		}
		
		else if (line[0] == '#'){ 
		
			// comment line
			
		}
		else {
			// I don't know what this is
		}
	}
	setData();
}

void MeshObject::setData(){
	printf("Setting data\n");
	if (program == 0){
		fprintf(stderr, "Can't set data - no GLSL program given to this meshobject\n");
		return;
	}
	max = vec3(FLT_MIN, FLT_MIN, FLT_MIN);
	min = vec3(FLT_MAX, FLT_MAX, FLT_MAX);
	for (int i = 0; i < vertices.size(); i++){
		
		if (vertices[i].x > max.x){
			max.x = vertices[i].x;
		}
		if (vertices[i].y > max.y){
			max.x = vertices[i].y;
		}
		if (vertices[i].z > max.z){
			max.x = vertices[i].z;
		}
		
		if (vertices[i].x < min.x){
			max.x = vertices[i].x;
		}
		if (vertices[i].y < min.y){
			max.x = vertices[i].y;
		}
		if (vertices[i].z < min.z){
			max.x = vertices[i].z;
		}
	
	}

	glBindBuffer(GL_ARRAY_BUFFER,vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER,
			vertices.size()*sizeof(vertex),
			&vertices[0],
			GL_STATIC_DRAW
	);
			
	glBindBuffer(GL_ARRAY_BUFFER,vbo_normals);
	glBufferData(GL_ARRAY_BUFFER,
			normals.size()*sizeof(vertex),
			&normals[0],
			GL_STATIC_DRAW
	);
	
	glBindBuffer(GL_ARRAY_BUFFER,vbo_texcoords);
	glBufferData(GL_ARRAY_BUFFER,
			texcoords.size()*sizeof(texcoord),
			&texcoords[0],
			GL_STATIC_DRAW
	);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			elements.size()*sizeof(unsigned int),
			&elements[0],
			GL_STATIC_DRAW
	);
	
	const char * attribute_name, * uniform_name;
	
	attribute_name = "vertex";
	att_vertex = glGetAttribLocation(program, attribute_name);
	if (att_vertex == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}
	
	attribute_name = "normal";
	att_normal = glGetAttribLocation(program, attribute_name);
	if (att_normal == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}
	
	attribute_name = "texcoord";
	att_texcoord = glGetAttribLocation(program, attribute_name);
	if (att_normal == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}
	
	uniform_name = "tex";
	uniform_tex = glGetUniformLocation(program, uniform_name);
	if (uniform_tex == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_tex);
	}
}

void MeshObject::draw(){

	glUniform1i(uniform_tex, 0);
	
	glEnableVertexAttribArray(att_vertex);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glVertexAttribPointer(
		att_vertex,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		0
	);
	
	glEnableVertexAttribArray(att_texcoord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_texcoords);
	glVertexAttribPointer(
		att_texcoord,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		0
	);

	glEnableVertexAttribArray(att_normal);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
	glVertexAttribPointer(
		att_normal,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		0
	);
	
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	
	
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE,&size);
	glDrawElements(GL_TRIANGLES, size/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	 
	 
	glDisableVertexAttribArray(att_normal);
	glDisableVertexAttribArray(att_vertex); 
	 
	if (int err = glGetError()){
		fprintf(stderr, "error in draw: %s\n", gluErrorString(err));
		exit(0);
	}

}


