#include "ObjectPool.h"

ObjectPool::ObjectPool(){
	current_index = 0;

}
Object * ObjectPool::getObject(){
	Object * object;
	if (!free_objects.size()){
		int current_size = objects.size();
		objects.reserve(current_size + 256);
		
		for (int j = 0; j<256; j++){
			Object * obj = new Object();
			obj->setIndex(current_index);
			current_index ++;
			objects.push_back(obj);
			free_objects.push(current_size+j);
		}
	}
	
	int free_index = free_objects.top();
	free_objects.pop();
	
	object = objects[free_index];
	object->activate();
	return object;
	
}

void ObjectPool::freeObject(Object * object){
	object->deactivate();
	free_objects.push(object->getIndex());
}

void ObjectPool::update(){
	for (int i = 0; i < objects.size(); i++){
		if (objects[i]->isActive()){
			objects[i]->update();
		}
	}
}

void ObjectPool::draw(){
	for (int i = 0; i < objects.size(); i++){	
		if (objects[i]->isActive()){
			objects[i]->draw();
		}
	}
}

Projectile * ProjectilePool::getObject(){
	Projectile * object;
	if (!free_objects.size()){
		int current_size = objects.size();
		objects.reserve(current_size + 256);
		
		for (int j = 0; j<256; j++){
			Projectile * obj = new Projectile();
			obj->setIndex(current_index);
			current_index ++;
			objects.push_back(obj);
			free_objects.push(current_size+j);
		}
	}
	
	int free_index = free_objects.top();
	free_objects.pop();
	
	object = objects[free_index];
	object->init();
	object->activate();
	return object;
}

void ProjectilePool::update(){
	for (int i = 0; i < objects.size(); i++){
		if (objects[i]->isActive()){
			if (objects[i]->isAlive()){
				objects[i]->update();
			}
			else freeObject(objects[i]);
		}
	}
}

void ProjectilePool::draw(){
	for (int i = 0; i < objects.size(); i++){	
		if (objects[i]->isActive()){
			objects[i]->draw();
		}
	}
}

Ship * ShipPool::getObject(){
	Ship * object;
	if (!free_objects.size()){
		int current_size = objects.size();
		objects.reserve(current_size + 256);
		
		for (int j = 0; j<256; j++){
			Ship * obj = new Ship();
			obj->setIndex(current_index);
			current_index ++;
			objects.push_back(obj);
			free_objects.push(current_size+j);
		}
	}
	
	int free_index = free_objects.top();
	free_objects.pop();
	
	object = objects[free_index];
	object->activate();
	return object;
}

void ShipPool::update(){
	for (int i = 0; i < objects.size(); i++){
		if (objects[i]->isActive()){
			objects[i]->update();
		}
	}
}

void ShipPool::draw(){
	for (int i = 0; i < objects.size(); i++){	
		if (objects[i]->isActive()){
			objects[i]->draw();
		}
	}
}

Beam* BeamPool::getObject(){
	Beam * object;
	if (!free_objects.size()){
		int current_size = objects.size();
		objects.reserve(current_size + 256);
		
		for (int j = 0; j<256; j++){
			Beam * obj = new Beam();
			obj->setIndex(current_index);
			current_index ++;
			objects.push_back(obj);
			free_objects.push(current_size+j);
		}
	}
	
	int free_index = free_objects.top();
	free_objects.pop();
	
	object = objects[free_index];
	object->init();
	object->activate();
	return object;
}

void BeamPool::update(){
	for (int i = 0; i < objects.size(); i++){
		if (objects[i]->isActive()){
			objects[i]->update();
		}
	}
}

void BeamPool::draw(){
	glDisable(GL_DEPTH_TEST);
	for (int i = 0; i < objects.size(); i++){	
		if (objects[i]->isActive()){
			objects[i]->draw();
		}
	}
	glEnable(GL_DEPTH_TEST);
}

