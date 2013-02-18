#include "GameSpace.h"

GameSpace * GameSpace::instance = NULL;

GameSpace * GameSpace::getInstance(){
	if (instance == NULL) instance = new GameSpace();
	return instance;
}

GameSpace::GameSpace(){
	
	proj_pool = new ProjectilePool();
	ship_pool = new ShipPool();
	beam_pool = new BeamPool();
	col_manager = new CollisionManager(proj_pool, beam_pool, ship_pool);

}

void GameSpace::update(){
	
	proj_pool->update();
	ship_pool->update();
	beam_pool->update();
	col_manager->checkCollisions();
}

void GameSpace::draw(){
	proj_pool->draw();
	beam_pool->draw();
	ship_pool->draw();
	
}
