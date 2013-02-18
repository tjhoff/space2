#include "CollectionDrawable.h"

using namespace std;

CollectionDrawable::CollectionDrawable(){
	program = 0;
}

CollectionDrawable::CollectionDrawable(unsigned int shader_program){
	program = shader_program;
	glGenBuffers(1, &vbo_vertices);
	glGenBuffers(1, &vbo_texcoords);
	glGenBuffers(1, &ibo_elements);
	generateField();
	setData();
	
}

void CollectionDrawable::generateField(){

	int index_index = 0;

	for (int i = 0; i < 10000; i++){
		vec2 xy = randSpread(vec2(0,0), 10000.0);
		float x = xy.x;
		float y = xy.y*.1;
		float z = -rand()%9800 - 200;
		vec3 pos(x,y,z);
		
		vertex v;
		texcoord t;
		
		v.x = pos.x - 10.0;
		v.y = pos.y - 10.0;
		v.z = pos.z;
		
		t.s = 0;
		t.t = 1;
		
		vertices.push_back(v);
		texcoords.push_back(t);
		
		v.x = pos.x - 10.0;
		v.y = pos.y + 10.0;
		v.z = pos.z;
		
		t.s = 0;
		t.t = 0;
		
		vertices.push_back(v);
		texcoords.push_back(t);
		
		v.x = pos.x + 10.0;
		v.y = pos.y - 10.0;
		v.z = pos.z;
		
		t.s = 1;
		t.t = 1;
		
		vertices.push_back(v);
		texcoords.push_back(t);
		
		v.x = pos.x + 10.0;
		v.y = pos.y + 10.0;
		v.z = pos.z;
		
		t.s = 1;
		t.t = 0;
		
		vertices.push_back(v);
		texcoords.push_back(t);
		
		elements.push_back(index_index+0);
		elements.push_back(index_index+1);
		elements.push_back(index_index+2);
		
		elements.push_back(index_index+1);
		elements.push_back(index_index+2);
		elements.push_back(index_index+3);
		
		index_index += 4;
		
		
	}
	printf("%i vertices\n", vertices.size());
	printf("%i elements\n", elements.size());
	printf("%i size\n", sizeof(vec3));
}

void CollectionDrawable::setData(){
	printf("Setting data\n");
	if (program == 0){
		fprintf(stderr, "Can't set data - no GLSL program given to this CollectionDrawable\n");
		return;
	}

	glBindBuffer(GL_ARRAY_BUFFER,vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER,
			vertices.size()*sizeof(vertex),
			&vertices[0],
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
	
	const char * attribute_name, *uniform_name;
	
	attribute_name = "vertex";
	att_vertex = glGetAttribLocation(program, attribute_name);
	if (att_vertex == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}
	
	attribute_name = "texcoord";
	att_texcoords = glGetAttribLocation(program, attribute_name);
	if (att_texcoords == -1) {
		fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
	}
	
	uniform_name = "tex";
	uniform_tex = glGetUniformLocation(program, uniform_name);
	if (uniform_tex == -1) {
		fprintf(stderr, "Could not bind uniform %s\n", uniform_tex);
	}
}

void CollectionDrawable::draw(){

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
	
	glEnableVertexAttribArray(att_texcoords);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_texcoords);
	glVertexAttribPointer(
		att_texcoords,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		0
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	
	
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE,&size);
	glDrawElements(GL_TRIANGLES, size/sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	 
	glDisableVertexAttribArray(att_vertex); 
	glDisableVertexAttribArray(att_texcoords); 
	 
	if (int err = glGetError()){
		fprintf(stderr, "error in draw: %s\n", gluErrorString(err));
		exit(0);
	}

}


