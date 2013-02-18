#pragma once

#include "ObjectPool.h"
#include "CollisionManager.h"

class GameSpace{
	public:
		static GameSpace * getInstance();
		GameSpace();
		void update();
		void draw();
	//private:
		
		CollisionManager * col_manager;
		ProjectilePool * proj_pool;
		ShipPool * ship_pool;
		BeamPool * beam_pool;
		Ship * player;
	private:
		static GameSpace * instance;
};
