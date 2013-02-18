#include "Projectile.h"

void Projectile::setFaction(int afaction){
	faction = afaction;
}

int Projectile::getFaction(){
	return faction;
}

void Projectile::update(){
	pos = pos + vel;
	rot = rot + ang_vel;
	range -= 1;
	if (range < 0){
		alive = 0;
	}
}

void Projectile::init(){
	alive = 1;
}

void Projectile::kill(){
	alive = 0;
}

bool Projectile::isAlive(){
	return alive;
}

void Projectile::setRange(float nrange){

	range = nrange;

}

void Projectile::setLen(float nlen){
	len = nlen;
}

void Projectile::draw(){
	glPushMatrix();
	glColor3f(1,1,1);
	float size = .5;
	glTranslatef(pos.x, pos.y, 0);
	glRotatef(degrees(rot),0,0,1);
	glBegin(GL_TRIANGLES);
		glTexCoord2f(1,0);
		glVertex2f(+size, +size);
		glTexCoord2f(0,0);
		glVertex2f(-size, +size);
		glTexCoord2f(1,1);
		glVertex2f(+size, -size);
		
		glTexCoord2f(0,1);
		glVertex2f(-size, -size);
		glTexCoord2f(0,0);
		glVertex2f(-size, +size);
		glTexCoord2f(1,1);
		glVertex2f(+size, -size);
	glEnd();
	size = .2;
	glColor3f(.5,.5,.5);
	glBegin(GL_TRIANGLES);
		glTexCoord2f(1,0);
		glVertex2f(0, +size);
		glTexCoord2f(0,0);
		glVertex2f(-len, +size);
		glTexCoord2f(1,1);
		glVertex2f(0, -size);
		
		glTexCoord2f(0,1);
		glVertex2f(-len, -size);
		glTexCoord2f(0,0);
		glVertex2f(-len, +size);
		glTexCoord2f(1,1);
		glVertex2f(0, -size);
	glEnd();
	
	glPopMatrix();
}
