#pragma once
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>
#include "Vec2.h"
#include <assert.h>
#include <stdio.h>

class Object{
	public:
		Object();
		virtual void init(){};
		virtual void update(){
			pos = pos + vel;
			rot = rot + ang_vel;
		};
		virtual void draw(){};
		void addForce(vec2 force);
		void rotate(float amount);
		vec2 getPos();
		vec2 getVel();
		float getAngVel();
		float getRot();
		float getMass();
		void setPos(vec2 npos);
		void setVel(vec2 nvel);
		void setAngVel(float navel);
		void setRot(float nrot);
		void setMass(float nmass);
		void activate();
		void deactivate();
		bool isActive(){
			return active;
		}
		int getIndex(){
			return index;
		}; 
		void setIndex(int nindex){
			index = nindex;
		};
		
	// technically private
		int turning;
		int index;
		vec2 pos;
		vec2 vel;
		float ang_vel;
		float rot;
		float mass;
		int active;
};
