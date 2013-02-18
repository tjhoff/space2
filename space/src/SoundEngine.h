#pragma once

#include <SFML/Audio.hpp>
#include <stdio.h>
#include <map>
#include <stack>
#include <assert.h>

class SoundEngine{
	public:
		static SoundEngine * getInstance();
		void playSound(int id);
		void loadSoundFile(std::string name);
		int loadSound(std::string name, bool looping = false);
		void setPosition(int id, float x, float y);
		void stopSound(int id);
		void setVolume(int id, float vol);
		void releaseID(int id);
		void setListenerPosition(float x, float y);
	private:
		static SoundEngine * instance;
		int s_id;
		std::map<std::string, sf::SoundBuffer*> soundLib;
		std::map<int, sf::Sound*> sounds;
		std::stack<int> freeSounds;
};
