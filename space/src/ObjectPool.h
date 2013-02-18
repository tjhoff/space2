#pragma once
#include <vector>
#include <stack>
#include "Object.h"
#include "Ship.h"
#include "Projectile.h"
#include "Beam.h"

class ObjectPool{
	public:
		ObjectPool();
		virtual Object * getObject();
		virtual void freeObject(Object * obj);
		virtual void update();
		virtual void draw();
		std::stack<int> free_objects;
		std::vector<Object*> objects;
		int current_index;
		
};

class ProjectilePool: public ObjectPool{
	public:
		Projectile * getObject();
		std::vector<Projectile*> objects;
		void draw();
		void update();
};

class ShipPool: public ObjectPool{
	public:
		Ship * getObject();
		std::vector<Ship*> objects;
		void draw();
		void update();
};

class BeamPool: public ObjectPool{
	public:
		Beam * getObject();
		std::vector<Beam*> objects;
		void draw();
		void update();
};
