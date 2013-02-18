#pragma once

#define GL_GLEXT_PROTOTYPES
#include "Vec2.h"
#include "Vec3.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_PARTICLES 8192

struct particle{
	vec2 pos;
	vec2 vel;
	float rot;
	int life;
	float ratio;
	vec3 color;
};



class ParticleEngine{

	public:
		static ParticleEngine *getInstance();
		ParticleEngine();
		void update();
		void draw();
		void createParticles(vec2 pos, vec2 dir, vec3 color, int num, float spread = 1.0);
	private:
		static ParticleEngine* instance;
		int current_particle;
		particle * particles;
};
