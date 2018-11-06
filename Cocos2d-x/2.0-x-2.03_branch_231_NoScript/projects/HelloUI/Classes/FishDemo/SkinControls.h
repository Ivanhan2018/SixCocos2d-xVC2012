#ifndef SKIN_CONTROLS_H
#define SKIN_CONTROLS_H
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

namespace UI
{
	CCEditBox* createEditBox(CCEditBoxDelegate* pDelegate, CCRect rcEditBox, const char *file, const char *PlaceHolder, int MaxLength,const char* pFontName="Î¢ÈíÑÅºÚ", int fontSize=20,EditBoxInputFlag inputFlag=kEditBoxInputFlagInitialCapsAllCharacters,EditBoxInputMode inputMode=kEditBoxInputModeSingleLine,KeyboardReturnType returnType=kKeyboardReturnTypeDefault);
       
	CCControlButton *createButton(CCObject* target, CCPoint pt, SEL_CCControlHandler action, CCLabelTTF *titleButton, const char *normalImg,const char *selectImg=NULL, const char * HighlightedImg=NULL, const char * DisabledImg = NULL);
};




#endif