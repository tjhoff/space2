#include "ParticleEngine.h"

ParticleEngine* ParticleEngine::instance = NULL;

ParticleEngine * ParticleEngine::getInstance(){
	if (!instance) instance = new ParticleEngine();
	return instance;
}

ParticleEngine::ParticleEngine(){
	particles = new particle[MAX_PARTICLES];
	current_particle = 0;
	for (int i = 0; i< MAX_PARTICLES; i++){
		particles[i].life = 0;
		particles[i].pos = vec2(0,0);
		particles[i].vel = vec2(0,0);
		particles[i].color = vec3(0,0,0);
	}

}

void ParticleEngine::update(){
	for (int i = 0; i<MAX_PARTICLES; i++){
		if (particles[i].life <= 0.0){
			continue;
		}
		
		particles[i].pos = particles[i].pos + particles[i].vel;
		particles[i].life --;
		particles[i].ratio = particles[i].life / 70.0;
	}
}

void ParticleEngine::draw(){

	float left, right, top, bottom;
	float ratio, size;
	vec2 p_pos;

	glBegin(GL_TRIANGLES);
	
	for (int i =0; i < MAX_PARTICLES; i++){
		if (particles[i].life <= 0.0){
			continue;
		}
		ratio = particles[i].ratio;
		vec3 color = particles[i].color;
		//glColor4f(ratio*.6,ratio*.3,ratio*.2,.2*ratio);
		glColor3f(ratio*10*color.x, ratio*2*color.y, ratio*color.z);
		p_pos = particles[i].pos;
		size = .5;
		double as, ac;
		sincos(particles[i].rot, &as, &ac);
		
		vec2 tr = p_pos + vec2(2*ac-as, 2*as+ac);
		vec2 tl = p_pos + vec2(-2*ac-as, -2*as+ac);
		vec2 br = p_pos + vec2(2*ac-(-as), 2*as-ac);
		vec2 bl = p_pos + vec2(-2*ac-(-as), -2*as-ac);
		
		glTexCoord2f(1,0);
		glVertex2f(tr.x,tr.y);
		glTexCoord2f(0,0);
		glVertex2f(tl.x, tl.y);
		glTexCoord2f(1,1);
		glVertex2f(br.x, br.y);
		
		glTexCoord2f(0,1);
		glVertex2f(bl.x, bl.y);
		glTexCoord2f(0,0);
		glVertex2f(tl.x, tl.y);
		glTexCoord2f(1,1);
		glVertex2f(br.x, br.y);
	}
	
	glEnd();
}

void ParticleEngine::createParticles(vec2 pos, vec2 dir, vec3 color, int num, float spread){

	float x;
	float y;
	for (int i = 0; i < num; i++){
		particles[current_particle].life = 20 + rand()%50;
		particles[current_particle].pos = pos;
		vec2 vel = randSpread(dir, spread);
		particles[current_particle].vel = vel;
		particles[current_particle].rot = atan2(vel.y, vel.x);
		particles[current_particle].color = color;
		current_particle++;
		if (current_particle > MAX_PARTICLES-1){
			current_particle = 0;
		}
		
	}

}
