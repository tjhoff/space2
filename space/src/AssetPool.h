#pragma once
#include "VBODrawable.h"
#include "Texture.h"
#include <assert.h>
#include <map>

class AssetPool{
	public:
		static AssetPool * getInstance();
		void loadDrawable(std::string mesh, std::string shader);
		void loadTexture(std::string texture);
		VBODrawable * getDrawable(std::string name);
		unsigned int getTexture(std::string name);
	private:
		static AssetPool * instance;
		std::map<std::string, VBODrawable*> drawables;
		std::map<std::string, unsigned int> textures;
};
