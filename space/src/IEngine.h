//////////////////////////////////////////
///           IEngine.h
//////////////////////////////////////////

#pragma once

#define GL_GLEXT_PROTOTYPES
#include <math.h>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <stdio.h>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Vec2.h"
#include "Vec3.h"
#include "Text.h"
#include "Collision.h"
#include "Window.h"
#include "Texture.h"
#include "InfoText.h"
#include "ParticleEngine.h"
#include "CollectionDrawable.h"
#include "Object.h"
#include "Ship.h"
#include "GameSpace.h"
#include "SoundEngine.h"
#include "AssetPool.h"
#include "GLWindow.h"
#include <vector>
#include <list>
#include <stack>

struct TempText{
	vec2 pos;
	vec2 vel;
	char str[64];
	int life;
};

class IEngine
{
	public:

		IEngine(int argc, char** argv);
		void initGL(int argc, char** argv);
		void checkKeys();
		void drawScene();
		void update();
		void resize(int width, int height);
		int begin();
		
		// ext crap

		//
		
	private:
	
		// ext crap
		
		CollectionDrawable * cd;
		
		GameSpace * game;
		
		ParticleEngine * p;
		
		Shader * s;
		
		std::stack<int> free_dmgtext;
		std::list<TempText> dmgtext;
		
		InfoText * info;
		
		int want_to_quit;
		
		int cooldown;
		
		float offset;
		
		unsigned int shot_tex;
		unsigned int ship_tex;
		unsigned int shit_tex;
		int shot_count;
		int shots_reserved;
		
		vec2 mouseCoords;
		
		Window w;
		
		mousebutton mb;
		
		//
	
		double m_time;
		sf::Window* m_window;
		GLWindow * window_dim;
		sf::Clock* m_clock;
		
		bool running;
		
		int frames;
		float time;
		float fps;
		float m_updateRate;
		
		vec3 cameraPos;
		
		float gl_width;
		float gl_height;
		
		float gl_min_width;
		float gl_min_height;
		
};

