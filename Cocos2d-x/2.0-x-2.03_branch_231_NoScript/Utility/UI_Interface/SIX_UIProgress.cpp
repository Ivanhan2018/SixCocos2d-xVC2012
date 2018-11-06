#include "SIX_UIProgress.h"

void *SIX_UIProgress::GetInterface(const char *pstrName)
{
	if(!_stricmp(pstrName,"UIProgress")) 
		return static_cast<SIX_UIProgress*>(this);
	else if(!_stricmp(pstrName,"UIControl")) 
		return static_cast<SIX_UIControl*>(this);
	return 0;
}

CCString SIX_UIProgress::GetClass() const
{
	return "UIProgress";
}

void SIX_UIProgress::draw()
{

}

