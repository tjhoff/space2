#pragma once
#include "Object.h"

class Projectile: public Object{
	public:
		void init();
		void update();
		void draw();
		int getFaction();
		void setFaction(int faction);
		void setRange(float nrange);
		void setLen(float nlen);
		bool isAlive();
		void kill();
	private:
		float len;
		int faction;
		float range;
		bool alive;
		
};

