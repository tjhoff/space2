#pragma once
#include "Object.h"
#include "ParticleEngine.h"
#include "VBODrawable.h"
#include "Component.h"
#include <vector>

class Ship: public Object{
	public:
		void init();
		void update();
		void draw();
		
		//
		// INTERACTION FUNCTIONS
		//
		
		void accelerate(float amount);
		void stabilize();
		void stabilize(vec2 velvec);
		void turn(float amount);
		void fire();
		
		//
		//
		//
		
		int getFaction();
		void setFaction(int faction);
		float getTurnDamping();
		void setTurnDamping(float nturn);
		void setAsPlayer();
		void damage(float amount);
		void setHull(float nhull);
		float getHull();
		bool isAccelerating();
		std::vector<Weapon *> getWeapons();
	private:
		std::vector<Component * > components;
		std::vector<Weapon * > weapons;
		bool accelerating;
		float hull;
		int player;
		int faction;
		float turn_damping;
		ParticleEngine * p;
};
