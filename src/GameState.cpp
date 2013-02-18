#include "GameState.h"

static unsigned int time_in_frames;

unsigned int GameState::getGameTime(){
	return time_in_frames;
}

void GameState::setGameTime(unsigned int time){
	time_in_frames = time;
}
