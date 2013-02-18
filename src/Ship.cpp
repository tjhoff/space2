#include "Ship.h"

//
//	CIRCULAR INHERITANCE FILES
//

#include "GameSpace.h"
#include "AssetPool.h"

void Ship::init(){
	faction = 0;
	player = 0;
	hull = 100.0;

	
	int type = 1;
	mass = 100.0;
	
	if (type == 1){
		Component * c = new Component(this, vec3(0,0,0),2, 0, "cockpit");
		components.push_back(c);
		
		c = new Component(this, vec3(0,3,0),3, PI/2.0, "wing");
		components.push_back(c);
		
		c = new Component(this, vec3(0,-3,0),3, -PI/2.0, "wing");
		components.push_back(c);
		
		c = new Engine(this, vec3(-1,4,1), 2, 0, "engine2");
		components.push_back(c);
		
		c = new Engine(this, vec3(-1,5,-1), 2, 0, "engine2");
		components.push_back(c);
		
		c = new Engine(this, vec3(-1,-5,-1), 2, 0, "engine2");
		components.push_back(c);
		
		c = new Engine(this, vec3(-1,-4,1), 2, 0, "engine2");
		components.push_back(c);
		
		
		c = new Weapon(this, vec3(-2,0,0), 6, 0, "cannon");
		((Weapon*) c)->setFireRate(50);
		components.push_back(c);
		weapons.push_back((Weapon*)c);
		
		c = new Weapon(this, vec3(-2,-6,0), 3, 0, "cannon");
		((Weapon*) c)->setFireRate(100);
		components.push_back(c);
		weapons.push_back((Weapon*)c);
		
		c = new Weapon(this, vec3(-2,6,0), 3, 0, "cannon");
		((Weapon*) c)->setFireRate(100);
		components.push_back(c);
		weapons.push_back((Weapon*)c);
		
		
	
	}
	
}

std::vector<Weapon *> Ship::getWeapons(){
	return weapons;
}

bool Ship::isAccelerating(){
	return accelerating;
}


void Ship::setHull(float nhull){
	hull=nhull;
}

float Ship::getHull(){
	return hull;
}

void Ship::setAsPlayer(){
	player = 1;
}

void Ship::update(){
	if (hull > 0){
	if (!player){
	
		
		GameSpace * game = GameSpace::getInstance();
		vec2 blah;
		double as, ac;
		sincos(game->player->rot, &as, &ac);
		

		vec2 diff;
		int go = 0;
		diff = game->player->getPos() - pos;
		float dist = (diff).length();
		
		//
		// IMPLEMENTED FLOCKING SPREAD
		//
		
		for (int i = 0; i < game->ship_pool->objects.size(); i++){
			Ship * iship = game->ship_pool->objects[i];
			if (iship->getIndex() == getIndex()){
				continue;
			}
			vec2 sdiff = pos - iship->getPos();
			if (sdiff.length() > 20.0){
				continue;
			}
			
			else{
				addForce(sdiff.normalize()*1);
			}
			
		}
		
		vec2 vdiff = vel- game->player->getVel();
		float l = vdiff.length();
		if (dist < 200){
			
			
			double as, ac;
			sincos(rot, &as, &ac);
			float d_dot = dot(diff, vec2(ac, as));
			d_dot = acos(d_dot / diff.length());
			if (fabs(d_dot) < .1){
				fire();
			}
			if (l > 0.1){
				diff = vdiff*-10;
				go = 1;
			}
			else stabilize(game->player->getVel());
		}
		else if (dist < 800){
			double as, ac;
			sincos(rot, &as, &ac);
			float d_dot = dot(diff, vec2(ac, as));
			d_dot = acos(d_dot / diff.length());
			if (fabs(d_dot) < .1){
				fire();
			}
			if (l > 1.0){
				diff = vdiff*-1;
				go = 1;
			}
			else{
				go = 1;
				stabilize(game->player->getVel());
			}
		}
		 
		float mrot = atan2(diff.y, diff.x);
		float norm_rot;
		
		
		norm_rot = rot;
		
		while (norm_rot<=-PI) norm_rot+=PI*2;
		while (norm_rot>PI) norm_rot-=PI*2;
			
		float adiff = mrot-norm_rot;
		
		int direction = 1;
		
		if (fabs(adiff) > PI){
			direction = -1;
		}
		
		if (fabs(adiff) > .02 ){
			turn(.02 * direction * (adiff < 0 ? -1 : 1));
		}
		else {
			turn(adiff);
		}
		//rot = norm_rot;
		if (go && adiff < .04) accelerate(1.0);
	}
	}
	for(int i =0; i < components.size(); i++){
		components[i]->update();
	}	
	
	pos = pos + vel;
	rot = rot + ang_vel;
	ang_vel = 0;
	turning = 0;
}

void Ship::accelerate(float amount){
	double as, ac;
	sincos(rot, &as, &ac);
	vec2 addvec = vec2(ac, as)*amount;
	addForce(addvec);
	
	
	vec2 fixturePosition(-7,2);
	
	float mx = ac * fixturePosition.x + -as*fixturePosition.y;
	float my = as * fixturePosition.x + ac*fixturePosition.y;
	
	fixturePosition = vec2(-7,-2);
	
	mx = ac * fixturePosition.x + -as*fixturePosition.y;
	my = as * fixturePosition.x + ac*fixturePosition.y;
	if (amount > 0){
		accelerating = true;
	}
	
}

void Ship::turn(float amount){
	rotate(amount);
}

void Ship::stabilize(){
	vec2 delta = vel.normalize() * -.001;
	if (vel.length() < .001){
		delta = vel * -1;
	}
	vel = vel + delta;
}

void Ship::stabilize(vec2 velvec){
	vec2 delta = (vel-velvec).normalize() * -.001;
	if ((vel-velvec).length() < .001){
		delta = (vel-velvec) * -1;
	}
	vel = vel + delta;
}

void Ship::fire(){
	for(int i =0; i < weapons.size(); i++){
		weapons[i]->fire();
	}
}

void Ship::damage(float amount){
	hull-=amount;
}

void Ship::draw(){
	glPushMatrix();
	
	glColor3f(1,hull/100.0,hull/100.0);
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(degrees(rot), 0,0,1);
	
	for(int i =0; i < components.size(); i++){
		components[i]->draw();
	}	
		
	glPopMatrix();
	accelerating = 0;
}

float Ship::getTurnDamping(){
	return turn_damping;
}

void Ship::setTurnDamping(float nturn){
	turn_damping = nturn;
}

void Ship::setFaction(int afaction){
	faction = afaction;
}

int Ship::getFaction(){
	return faction;
}
