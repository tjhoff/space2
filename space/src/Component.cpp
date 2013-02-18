#include "Component.h"
#include "Ship.h"
#include "GameSpace.h"

Component::Component(){
	init();
}

Component::Component(Ship * mship, vec3 mpos, float mscale, float mrot, std::string vbodname){
	drawable = AssetPool::getInstance()->getDrawable(vbodname);
	pos = mpos;
	scale = mscale;
	rot = mrot;
	ship = mship;
	init();
	tex = AssetPool::getInstance()->getTexture("metal");
}

Engine::Engine(Ship * mship, vec3 mpos, float mscale, float mrot, std::string vbodname){
	drawable = AssetPool::getInstance()->getDrawable(vbodname);
	pos = mpos;
	scale = mscale;
	rot = mrot;
	ship = mship;
	init();
	tex = AssetPool::getInstance()->getTexture("metal");
}

Weapon::Weapon(Ship * mship, vec3 mpos, float mscale, float mrot, std::string vbodname){
	drawable = AssetPool::getInstance()->getDrawable(vbodname);
	pos = mpos;
	scale = mscale;
	rot = mrot;
	ship = mship;
	init();
	tex = AssetPool::getInstance()->getTexture("metal");
}

void Component::init(){}

void Component::draw(){
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	glRotatef(degrees(rot),0,0,1);
	glScalef(scale, scale, scale);
	glBindTexture(GL_TEXTURE_2D, tex);
	
	
	drawable->draw();
	
	glPopMatrix();
}

void Component::update(){
	
}

void Engine::init(){
	exhaust = AssetPool::getInstance()->getTexture("exhaust");
	thrust_size = 0;	
}

void Engine::update(){

	if (ship->isAccelerating()){
		if (thrust_size < 2.0){
			thrust_size += .2;
		}
		else {
			thrust_size = 2.0 + (rand()%100)/200.0;
		}
	}

	if (thrust_size > .5 && !ship->isAccelerating()){
	
		thrust_size-=.5;
	
	}
	else if (!ship->isAccelerating()) thrust_size = 0;

}

void Engine::draw(){
	
	glPushMatrix();
	glTranslatef(pos.x,pos.y,pos.z);
	glRotatef(degrees(rot),0,0,1);
	glPushMatrix();
	glScalef(scale, scale, scale);
	glBindTexture(GL_TEXTURE_2D, tex);
	drawable->draw();
	glPopMatrix();
	
	glBindTexture(GL_TEXTURE_2D, exhaust);
	
	if (thrust_size > 0.1){
		float length = thrust_size*scale;
		float width = .5*scale;
		
		glBegin(GL_TRIANGLES);
			glTexCoord2f(1.0,0);
			glVertex2f(length-length, +width);
			glTexCoord2f(.1,0);
			glVertex2f(-length-length, +width);
			glTexCoord2f(1.0,1);
			glVertex2f(+length-length, -width);
		
			glTexCoord2f(.1,1);
			glVertex2f(-length-length, -width);
			glTexCoord2f(.1,0);
			glVertex2f(-length-length, +width);
			glTexCoord2f(1.0,1);
			glVertex2f(+length-length, -width);
		glEnd();
	}
	
	glPopMatrix();

}

void Weapon::init(){
	
	fire_rate= rand()%2 * 10 + 10;
	cooldown_count = fire_rate;
	beam = GameSpace::getInstance()->beam_pool->getObject();
	overheat = false;
	firing = false;
	last_firing = false;
}

void Weapon::setFireRate(int nfr){
	fire_rate = nfr;
}

int Weapon::getFireRate(){
	return fire_rate;
}

int Weapon::getCooldown(){
	return cooldown_count;
}

bool Weapon::isOverheating(){
	return overheat;
}

void Weapon::fire(){
	if ((!overheat)){
		firing = true;
	}
	/*if (!cooldown_count){
		Projectile * shot = GameSpace::getInstance()->proj_pool->getObject();
		double as, ac;
		sincos(ship->getRot() + rot, &as, &ac);
		
		float mx = ac * (pos.x) + -as*pos.y;
		float my = as * (pos.x) + ac*pos.y;
		shot->setPos(ship->getPos() + vec2(mx, my));
		shot->setVel(ship->getVel());
		shot->setRot(ship->getRot());
		shot->setMass(.1);
		shot->setRange(100);
		shot->addForce(vec2(ac,as) *force);
		shot->setLen(20);
		shot->setFaction(ship->getFaction());

		cooldown_count = fire_rate;
	}*/
}

void Weapon::update(){
	
	if (beam->isFiring() && !firing){
		beam->stopFire();
	}
	
	if (firing){
		double as, ac;
		sincos(ship->getRot() + rot, &as, &ac);
		float mx = ac * (pos.x) + -as*pos.y;
		float my = as * (pos.x) + ac*pos.y;
		beam->setFaction(ship->getFaction());
		beam->fire();
		beam->setStart(ship->getPos() +ship->getVel() + vec2(mx, my));
		beam->setEnd(ship->getPos() + ship->getVel()+ vec2(ac, as)*1000);
		cooldown_count +=1;
		if (cooldown_count >= fire_rate){
			overheat = true;
		}
	}

	else {
	
		if (cooldown_count > 0){
			cooldown_count --;
		
		}
		if (cooldown_count == 0) overheat = false;
	}
	firing = false;
	//last_firing = false;
}

