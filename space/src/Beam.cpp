#include "Beam.h"

void Beam::init(){
	color = vec3((rand()%100) / 100.0,(rand()%100) / 100.0,(rand()%100) / 100.0);
}

int Beam::getFaction(){
	return faction;
}


void Beam::setFaction(int nfaction){
	faction = nfaction;
}

void Beam::setStart(vec2 nstart){
	start = nstart;
}

void Beam::setEnd(vec2 nend){
	end = nend;
}

vec2 Beam::getStart(){
	return start;
}

vec2 Beam::getEnd(){
	return end;
}

void Beam::update(){

}

bool Beam::isFiring(){
	return beam_active;
}

void Beam::fire(){
	beam_active = true;
}

void Beam::stopFire(){
	beam_active = false;
}

void Beam::draw(){
	if (!beam_active) return;
	vec2 dir = (end-start).normalize();
	
	
	float xoff = -dir.y*1;
	float yoff = dir.x*1;

	//
	//	*----*
	//  |---/|
	//  |--/-|
	//  |-/--|
	//  |/---|
	//  *----*
	glColor3f(.3,1.0,.3);
	glBegin(GL_TRIANGLES);
	
		glTexCoord2f(1,0);
		glVertex2f(start.x + xoff, start.y + yoff);
		glTexCoord2f(0,0);
		glVertex2f(start.x - xoff, start.y - yoff);
		glTexCoord2f(0,1);
		glVertex2f(end.x - xoff, end.y - yoff);
		
		glTexCoord2f(0,1);
		glVertex2f(end.x - xoff, end.y - yoff);
		glTexCoord2f(1,1);
		glVertex2f(end.x + xoff, end.y + yoff);
		glTexCoord2f(1,0);
		glVertex2f(start.x + xoff, start.y + yoff);
		
	glEnd();
	
}
