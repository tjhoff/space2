#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Object.h"
class Beam: public Object{
	public:
		void init();
		void setStart(vec2 start);
		void setEnd(vec2 end);
		vec2 getStart();
		vec2 getEnd();
		void draw();
		void update();
		void fire();
		void stopFire();
		bool isFiring();
		int getFaction();
		void setFaction(int faction);
	private:
		int faction;
		vec3 color;
		bool beam_active;
		vec2 start;
		vec2 end;
};
