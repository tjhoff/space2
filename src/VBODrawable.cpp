#include "VBODrawable.h"

using namespace std;

VBODrawable::VBODrawable(string meshname, string shadername){

	string frag_path = string(SHADIR) + shadername + string(FRAGMENT_SUFFIX);
	string vertex_path = string(SHADIR) + shadername + string(VERTEX_SUFFIX);
	string mesh_path = string(MESHDIR) + meshname + string(MESH_SUFFIX);
	
	
	s = new Shader(vertex_path.c_str(), frag_path.c_str());
	m = new MeshObject(mesh_path.c_str(), s->getID());
	

}

void VBODrawable::draw(){
	s->bind();
	m->draw();
	s->release();
}
