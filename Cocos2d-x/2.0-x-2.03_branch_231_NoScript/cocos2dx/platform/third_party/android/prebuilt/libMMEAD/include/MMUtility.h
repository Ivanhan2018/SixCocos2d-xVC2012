#pragma once
#include "xorstr.h"
#include "MMEAD_Config.h"

class MMUtility {
public:
	MMUtility()
	{
		srand((unsigned int)time(0));
	}

	~MMUtility(){};

public:
	int RNDNUM(int min,int max);
	int s2n(char s);
};