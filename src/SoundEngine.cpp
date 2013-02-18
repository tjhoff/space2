#include "SoundEngine.h"

using namespace std;
using namespace sf;

SoundEngine * SoundEngine::instance = NULL;

SoundEngine * SoundEngine::getInstance(){
	if (!instance) instance = new SoundEngine();
	return instance;
}

void SoundEngine::loadSoundFile(string name){
	SoundBuffer *sb;
	sb = new SoundBuffer();
	sb->LoadFromFile(name);
	soundLib[name] = sb;
}

int SoundEngine::loadSound(string name, bool looping){
	SoundBuffer * sbp;
	if ((sbp = soundLib[name])==NULL){
		printf("Aint no %s\n", name.c_str());
		return -1;
		
	}
	Sound *s;
	if (freeSounds.size()){
		s = sounds[freeSounds.top()];
		freeSounds.pop();
	}
	
	else s = new Sound();
	s->SetLoop(looping);
	s->SetBuffer(*sbp);
	s->SetVolume(100.0);
	s->SetRelativeToListener(true);
	s->SetAttenuation(10.0);
	s->SetMinDistance(5.0);
	sounds[s_id] = s;
	s_id++;
	return s_id-1;
}

void SoundEngine::playSound(int id){
	assert(sounds[id]);
	sounds[id]->Play();
}

void SoundEngine::stopSound(int id){
	assert(sounds[id]);
	sounds[id]->Stop();
	
}

void SoundEngine::releaseID(int id){
	freeSounds.push(id);
	sounds[id]->Stop();
}

void SoundEngine::setPosition(int id, float x, float y){
	assert(sounds[id]);
	sounds[id]->SetPosition(x, 0, y);
}

void SoundEngine::setVolume(int id, float vol){
	assert(sounds[id]);
	sounds[id]->SetVolume(vol);
}

void SoundEngine::setListenerPosition(float x, float y){
	Listener::SetPosition(x, 0, y);
}
