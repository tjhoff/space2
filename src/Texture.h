#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#define TEXDIR "tex/"
#define TEX_SUFFIX ".png"

class Texture
{
    public:
        static GLuint loadTexture(std::string name);
        static GLuint loadNRNTexture(std::string img_path);
        static GLuint loadFromMemory(int width, int height, unsigned char* data);
        static void deleteTexture(GLuint texture_handle);
        
    //private:
        Texture();
};
