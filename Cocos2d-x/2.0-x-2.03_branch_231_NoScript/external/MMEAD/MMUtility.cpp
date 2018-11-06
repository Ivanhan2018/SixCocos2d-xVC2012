#include "MMUtility.h"

int MMUtility::RNDNUM(int min,int max)
{
	int rndnum = 0;

	rndnum = rand() % (max-min+1) + min;

	if (rndnum<min)
		rndnum=min;

	return rndnum;
}

int MMUtility::s2n(char s)
{
	if (s>=48 && s<=57)
		return s-48;
	else if (s>=65 && s<=70)
		return s-55;
	return 0;
}