#include "SkinControls.h"
//#include <string>

namespace UI
{

};

CCEditBox* UI::createEditBox(CCEditBoxDelegate* pDelegate, CCRect rcEditBox, const char *file, const char *PlaceHolder, int MaxLength,const char* pFontName/*="Î¢ÈíÑÅºÚ"*/, int fontSize/*=20*/,EditBoxInputFlag inputFlag/*=kEditBoxInputFlagInitialCapsAllCharacters*/,EditBoxInputMode inputMode/*=kEditBoxInputModeSingleLine*/,KeyboardReturnType returnType/*=kKeyboardReturnTypeDefault*/)
{
		CCEditBox *pEditBox = NULL;//CCEditBox::create(rcEditBox.size, CCScale9Sprite::create( file ));
		//pEditBox->setPosition(CCPoint(rcEditBox.getMinX(), rcEditBox.getMinY()));
		////pEditBox->setFont(pFontName, fontSize);
		////pEditBox->setPlaceholderFont(pFontName, fontSize);
		//pEditBox->setFontColor(ccBLACK);
		//pEditBox->setPlaceHolder(PlaceHolder);
		//pEditBox->setPlaceholderFontColor(ccWHITE);
		//pEditBox->setMaxLength(MaxLength);
		//pEditBox->setReturnType(returnType);
		//pEditBox->setInputFlag(inputFlag);
		//pEditBox->setInputMode(inputMode);
		//pEditBox->setDelegate(pDelegate);
		return pEditBox;
}


CCControlButton *UI::createButton(CCObject* target, CCPoint pt, SEL_CCControlHandler action, CCLabelTTF *titleButton, const char *normalImg, const char *selectImg/*=NULL*/, const char * HighlightedImg/*=NULL*/, const char * DisabledImg /*= NULL*/)
{
		return 0;
	 //   CCScale9Sprite *backgroundButton = CCScale9Sprite::create( normalImg );
		//CCControlButton *controlButton = CCControlButton::create( titleButton, backgroundButton );
		//controlButton->setTitleColorForState(ccWHITE, CCControlStateHighlighted);

		//if (NULL != selectImg)
		//{
		//	CCScale9Sprite * SelectImgScale9Sprite = CCScale9Sprite::create( selectImg );
		//	controlButton->setBackgroundSpriteForState(SelectImgScale9Sprite, CCControlStateSelected);
		//}
		//if (NULL != HighlightedImg)
		//{
		//	CCScale9Sprite *backgroundHighlightedButton = CCScale9Sprite::create( HighlightedImg );
		//	controlButton->setBackgroundSpriteForState(backgroundHighlightedButton, CCControlStateHighlighted);
		//}
		//if (NULL != DisabledImg)
		//{
		//	CCScale9Sprite *Scale9SpriteDisabled = CCScale9Sprite::create( DisabledImg );
		//	controlButton->setBackgroundSpriteForState(Scale9SpriteDisabled, CCControlStateDisabled);
		//}
		////if (rc.size.width >0 && rc.size.height >0 )
		////{
		////	controlButton->setContentSize( rc.size );
		////}
		//controlButton->setPosition( CCPoint(pt.x, pt.y) );
		//controlButton->addTargetWithActionForControlEvents(target, action, CCControlEventTouchDown);
		//return controlButton;
}
