#include "InfoText.h"

InfoText * InfoText::instance = NULL;

InfoText * InfoText::getInstance(){
	if (!instance) instance = new InfoText();
	return instance;
}

InfoText::InfoText(){

	int current_size = strings.size();
	strings.reserve(current_size +32);
	for (int i = 0; i < 32; i++){
		info_string * t = new info_string;
		t->dead = 1;
		strcpy(t->str, "zabbadoop");
		strings.push_back(t); 
		free_strings.push(current_size+i);
	}
	string_index = 0;
	
	SoundEngine * sengine = SoundEngine::getInstance();
	sengine->loadSoundFile("beep.wav");
	beep_noise = sengine->loadSound("beep.wav");
	sengine->setVolume(beep_noise, 20);

}

std::vector<info_string*> InfoText::getStrings(){
	return strings;
}

int InfoText::getMaxStringIndex(){
	return string_index;
}

void InfoText::addString(char* str, int level){
	
	if (!free_strings.size()){
		int current_size = strings.size();
		strings.reserve(current_size +32);
		for (int i = 0; i < 32; i++){
			info_string * t = new info_string;
			t->dead = 1;
			strcpy(t->str, "zabbadoop");
			strings.push_back(t);
			free_strings.push(current_size+i);
		}
	}
	
	info_string * info = strings[free_strings.front()];
	free_strings.pop();
	strcpy(info->str, str);
	
	switch (level){
		case NORMAL:
			info->color[0] = .7;
			info->color[1] = .7;
			info->color[2] = .7;
			break;
		case ALERT:
			info->color[0] = 1.0;
			info->color[1] = .6;
			info->color[2] = .2;
			break;
		case INFO:
			info->color[0] = .0;
			info->color[1] = .6;
			info->color[2] = .8;
			break;
		case EMERGENCY:
			info->color[0] = 1.0;
			info->color[1] = .0;
			info->color[2] = .0;
			break;
	}
	
	info->dead = 0;
	string_index ++;
	SoundEngine * sengine = SoundEngine::getInstance();
	sengine->playSound(beep_noise);
}
