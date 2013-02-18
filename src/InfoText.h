#pragma once
#include <vector>
#include <stack>
#include <queue>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "SoundEngine.h"

struct info_string{
	char str[256];
	float color[3];
	int dead;
};

enum LEVEL{
	NORMAL,
	ALERT,
	INFO,
	EMERGENCY
};

class InfoText{

	public:
		static InfoText * getInstance();
		InfoText();
		void addString(char* str, int level = NORMAL);
		std::vector<info_string*> getStrings();
		int getMaxStringIndex();
	private:
		static InfoText * instance;
		int string_index;
		std::vector<info_string*> strings;
		std::queue<int> free_strings;
		int beep_noise;

};
