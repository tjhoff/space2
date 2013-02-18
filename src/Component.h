#pragma once

#include "Vec3.h"
#include "VBODrawable.h"
#include "AssetPool.h"
#include "Projectile.h"
#include "Beam.h"
#include <string>

class Ship;

class Component{

	public:
		Component();
		Component(Ship * mship, vec3 mpos, float mscale, float mrot, std::string vbodname);
		virtual void init();
		virtual void draw();
		virtual void update();
	//private:
		Ship * ship;
		vec3 pos;
		float scale;
		float rot;
		VBODrawable * drawable;
		unsigned int tex;

};

class Engine: public Component{
	public:
		Engine(Ship * mship, vec3 mpos, float mscale, float mrot, std::string vbodname);
		void init();
		void draw();
		void update();
				
		unsigned int exhaust;
		float thrust_size;
};

class Weapon: public Component{
	public:
		Weapon(Ship * mship, vec3 mpos, float mscale, float mrot, std::string vbodname);
		void init();
		void update();
		void fire();
		void setFireRate(int nfr);
		int getCooldown();
		int getFireRate();
		bool isOverheating();
		
		Beam *beam;
		unsigned int exhaust;
		bool firing;
		bool last_firing;
		bool overheat;
		int fire_rate;
		int cooldown_count;
		float force;
		
};
