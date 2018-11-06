#include "Lamp.h"

Lamp::Lamp(const char *pszFilename, Result r_type)
{
	initWithFile(pszFilename);
	this->r_type = r_type;
}

Lamp::~Lamp(void)
{
}

void Lamp::draw(void)
{
	CCSprite::draw();
}