
#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#pragma once

#include "cocos2d.h"

#include <map>
#include <string>
using namespace cocos2d;

class Material
{
public:
	Material(void);
	void load_00(void);
	void load_01(void);
	void load_02(void);
	void load_03(void);
	void load_04(void);
	void load_05(void);
	void load_06(void);
	void load_07(void);
	void load_08(void);
	void load_09(void);
	void load_10(void);
	void load_11(void);
	void load_12(void);
	void load_13(void);
	void load_14(void);
	void load_15(void);
	void load_16(void);
	void load_17(void);
	void load_18(void);
	void load_19(void);
	void load_20(void);
	~Material(void);

public:
	CCTexture2D *fishTexture;
	CCTexture2D *shuiCaoTexture;

	CCAnimationCache animationCache;
	CCTexture2D *historyTexture[11];

	CCTexture2D *daoJiShiNumer;
	CCTexture2D *winerNumer;

	CCTexture2D *light_0;
	CCTexture2D *light_1;
	CCTexture2D *light_2;
#if 0
	CCMutableDictionary<int, CCAnimation*> lamp_Animatin_0;
	CCMutableDictionary<int, CCAnimation*> lamp_Animatin_1;
	CCMutableDictionary<int, CCAnimation*> lamp_Animatin_2;

	CCMutableDictionary<int, CCAnimation*> winer_Animatin_0;
#endif
	CCTexture2D *winer_Texture[11];

	CCTexture2D *sharkShootParticleTX;
	CCTexture2D *sharkFireParticleTX;

};

#endif 