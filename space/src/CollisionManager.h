#pragma once
#include "ObjectPool.h"
#include "Collision.h"
#include "InfoText.h"

class CollisionManager{
	public:
		CollisionManager(ProjectilePool * nproj, BeamPool * nbeam, ShipPool * nships);
		void checkCollisions();
	public:
		ProjectilePool * projectiles;
		ShipPool * ships;
		BeamPool * beams;
};
