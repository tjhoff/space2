#include "CollisionManager.h"

CollisionManager::CollisionManager(ProjectilePool * nproj, BeamPool * nbeam,  ShipPool * nships){
	projectiles = nproj;
	ships = nships;
	beams = nbeam;
}

void CollisionManager::checkCollisions(){
	for (int i = 0; i < ships->objects.size(); i++){
		if (!ships->objects[i]->isActive()) continue;
		vec2 ship_pos = ships->objects[i]->getPos();
		int faction = ships->objects[i]->getFaction();
		for (int j = 0; j < projectiles->objects.size(); j++){
			if (!projectiles->objects[j]->isActive())continue;
			if (faction == projectiles->objects[j]->getFaction()) continue;
			vec2 proj_pos = projectiles->objects[j]->getPos();
			vec2 diff = ship_pos - proj_pos;
			if ((diff).squaredLength() < pow(11,2)){
				
				
				Projectile * p = projectiles->objects[j];
				Ship * s = ships->objects[i];
				vec2 force = p->getVel() * p->getMass();
				
				s->addForce(force);
				s->damage(force.length());
				p->kill();
					
			}
		}
		for (int j = 0; j < beams->objects.size(); j++){
			
			if (!beams->objects[j]->isActive()) continue;
			if (!beams->objects[j]->isFiring()) continue;
			if (faction == beams->objects[j]->getFaction()) continue;
			vec2 ipos;
			
			Beam * b = beams->objects[j];
			Ship * s = ships->objects[i];
			
			if (rayCircleIntersect(ship_pos, 10, b->getEnd(),b->getStart(), ipos)){
				ParticleEngine::getInstance()->createParticles(ipos, s->getVel() + (ipos-ship_pos).normalize()*1.0, vec3(.9,.9,1), rand()%3, .3);
				b->setEnd(ipos);
			}
		}
	}
}
