#include "Object.h"

Object::Object(){
	ang_vel = 0;
	rot = 0;
	mass = 1;
	active = 0;
	turning = 0;
}


void Object::addForce(vec2 force){
	assert(mass>0);
	vel = vel + (force * (1/mass));
}

void Object::rotate(float amount){
	turning = 1;
	ang_vel += amount;
}

vec2 Object::getPos(){
	return pos;
}		
vec2 Object::getVel(){
	return vel;
}
float Object::getAngVel(){
	return ang_vel;
}
float Object::getRot(){
	return rot;
}
float Object::getMass(){
	return mass;
}
void Object::setPos(vec2 npos){
	pos = npos;
}
void Object::setVel(vec2 nvel){
	vel = nvel;
}
void Object::setAngVel(float navel){
	ang_vel = navel;
}
void Object::setRot(float nrot){
	rot = nrot;
}
void Object::setMass(float nmass){
	mass = nmass;
}
void Object::activate(){
	active = 1;
}
void Object::deactivate(){
	active = 0;
}
