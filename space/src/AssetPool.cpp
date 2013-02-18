#include "AssetPool.h"

using namespace std;

AssetPool * AssetPool::instance = NULL;

AssetPool * AssetPool::getInstance(){
	if (!instance) instance = new AssetPool();
	return instance;
}

void AssetPool::loadDrawable(string mesh, string shader){
	if (drawables[mesh]) return;
	drawables[mesh] = new VBODrawable(mesh, shader);
}

void AssetPool::loadTexture(string texture){
	if (textures[texture]) return;
	textures[texture] = Texture::loadTexture(texture);
}

unsigned int AssetPool::getTexture(string name){
	return textures[name];
}

VBODrawable * AssetPool::getDrawable(string name){
	VBODrawable * drawable = drawables[name];
	assert(drawable);
	return drawable;
}
