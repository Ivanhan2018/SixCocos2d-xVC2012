#include "Numbers.h"

Numbers::Numbers(CCTexture2D *pTexture, CCSize size, CCPoint position, float rotate, CCPoint hotspot, ALIGN align)
{
	for(int i = 0; i< MAX_NUMBER_LENGTH; i++)
	{
		numberList[i] = new NumberSprite(pTexture, size);
	}

	reset(position, rotate, hotspot, align);
}

void Numbers::reset(CCPoint position, float rotate, CCPoint hotspot, ALIGN align)
{
	this->ali = align;

	if (align == ALIGN_AT_LEFT)
	{
		CCPoint hp = hotspot;
		for(int i = 0; i < MAX_NUMBER_LENGTH; i++)
		{
			numberList[i]->setPosition(position);
			numberList[i]->setAnchorPoint(hp);
			numberList[i]->setRotation(rotate);
			hp.x -= 1;
		}
	} 
	else if (align == ALIGN_AT_CENTRE)
	{
		CCPoint hp = ccpAdd(ccp(MAX_NUMBER_LENGTH / 2, 0), hotspot);
		for(int i = 0; i < MAX_NUMBER_LENGTH; i++)
		{
			numberList[i]->setPosition(position);
			numberList[i]->setAnchorPoint(hp);
			numberList[i]->setRotation(rotate);
			hp.x -= 1;
		}
	}
	else
	{
		CCPoint hp = hotspot;
		for(int i = 0; i < MAX_NUMBER_LENGTH; i++)
		{
			hp.x += 1;
			numberList[i]->setPosition(position);
			numberList[i]->setAnchorPoint(hp);
			numberList[i]->setRotation(rotate);
		}
	}
}

Numbers::~Numbers(void)
{
}

void Numbers::setValue(int v, bool isShow)
{
	for (int i = 0; i < MAX_NUMBER_LENGTH; i++)
	{
		numberList[i]->setValue(0, false);
	}

	if (isShow)
	{
		int numLen = Numbers::GetNumderLength(v);
		int startIndex = 0;
		if(ali == ALIGN_AT_LEFT)
		{
			//从 MAX_NUMBER_LENGTH - 1 开始往前
			startIndex = numLen - 1;

		}
		else if (ali == ALIGN_AT_CENTRE)
		{
			//从 (MAX_NUMBER_LENGTH - （MAX_NUMBER_LENGTH - numLen)/2) - 1 开始往前
			startIndex = (MAX_NUMBER_LENGTH - (MAX_NUMBER_LENGTH - numLen)/2) - 1;
		}
		else
		{
			//从 numLen - 1 往前
			startIndex = MAX_NUMBER_LENGTH - 1;
		}
		int n = abs(v);
		int a = 0;
		do
		{
			a = n%10;
			numberList[startIndex]->setValue(a);
			startIndex--;
			n/=10;
		}while(n>0);

		if(v < 0)
		{
			numberList[startIndex]->setValue(10);
		}
	} 
}

int Numbers::GetNumderLength(int number)
{
	int i = 1;

	if(number < 0)
	{
		i++;
	}

	number = abs(number);
	while (number >= 10)
	{
		i++;
		number /= 10;
	}
	return i;
}