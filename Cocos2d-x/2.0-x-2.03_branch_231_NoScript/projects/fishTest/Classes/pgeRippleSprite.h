/* pgeRippleSprite.h*/

//
//  pgeRippleSprite.h
//  rippleDemo
//
//  Created by Lars Birkemose on 02/12/11.
//  Copyright 2011 Protec Electronics. All rights reserved.
//
// --------------------------------------------------------------------------
// import headers


// porting to cplusplus by wanghong.li (wanghong.li1029@163.com)on 04/01/12
// All rights reserved


#include "cocos2d.h"
#include <list>


// --------------------------------------------------------------------------
// defines


#define RIPPLE_DEFAULT_QUAD_COUNT_X             30         
#define RIPPLE_DEFAULT_QUAD_COUNT_Y             20 


#define RIPPLE_BASE_GAIN                        0.1f        // an internal constant


#define RIPPLE_DEFAULT_RADIUS                   500         // radius in pixels  
#define RIPPLE_DEFAULT_RIPPLE_CYCLE             0.25f       // timing on ripple ( 1/frequenzy )
#define RIPPLE_DEFAULT_LIFESPAN                 3.6f        // entire ripple lifespan


#define RIPPLE_CHILD_MODIFIER                   2.0f


// --------------------------------------------------------------------------
// typedefs


typedef enum {
	RIPPLE_TYPE_RUBBER,                                     // a soft rubber sheet
	RIPPLE_TYPE_GEL,                                        // high viscosity fluid
	RIPPLE_TYPE_WATER,                                      // low viscosity fluid
} RIPPLE_TYPE;


typedef enum {
	RIPPLE_CHILD_LEFT,
	RIPPLE_CHILD_TOP,
	RIPPLE_CHILD_RIGHT,
	RIPPLE_CHILD_BOTTOM,
	RIPPLE_CHILD_COUNT
} RIPPLE_CHILD;


typedef struct _rippleData {
	bool                    parent;                         // ripple is a parent
	bool                    childCreated[ 4 ];              // child created ( in the 4 direction )
	RIPPLE_TYPE             rippleType;                     // type of ripple ( se update: )
	cocos2d::CCPoint        center;                         // ripple center ( but you just knew that, didn't you? )
	cocos2d::CCPoint        centerCoordinate;               // ripple center in texture coordinates
	float                   radius;                         // radius at which ripple has faded 100%
	float                   strength;                       // ripple strength 
	float                   runtime;                        // current run time
	float                   currentRadius;                  // current radius
	float                   rippleCycle;                    // ripple cycle timing
	float                   lifespan;                       // total life span       
} rippleData;


// --------------------------------------------------------------------------
// pgeRippleSprite


typedef std::list<rippleData*>::iterator         RIPPLE_DATA_LIST;
typedef std::list<rippleData*>::reverse_iterator REVERSE_RIPPLE_DATA_LIST;


class CCpgeRippleSprite : public cocos2d::CCNode
{
public:
	CCpgeRippleSprite();
	~CCpgeRippleSprite();

	CC_SYNTHESIZE(cocos2d::CCTexture2D*, m_texture, Texture)
	CC_SYNTHESIZE(int, m_quadCountX, QuadCountX)
	CC_SYNTHESIZE(int, m_quadCountY, QuadCountY)
	CC_SYNTHESIZE(int, m_VerticesPrStrip, VerticesPrStrip)
	CC_SYNTHESIZE(int, m_bufferSize, BuffSize)
	CC_SYNTHESIZE(cocos2d::CCPoint*, m_vertice, Vertice)
	CC_SYNTHESIZE(cocos2d::CCPoint*, m_textureCoordinate, TextureCoordinate)
	CC_SYNTHESIZE(cocos2d::CCPoint*, m_rippleCoordinate, RippleCoordinate)
	CC_SYNTHESIZE_READONLY(bool*, m_edgeVertice, EdgeVertice)
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(std::list<rippleData*>, m_rippleList, RippleList)

public:
	static CCpgeRippleSprite* rippleSpriteWithFile(const char* filename);

	bool initWithFile(const char* filename);
	virtual void draw();
	void  update(float dt);
	void  addRipple(cocos2d::CCPoint &pos, RIPPLE_TYPE type, float strength);

protected:
	void  tesselate();
	void  addRippleChild(rippleData* parent, RIPPLE_CHILD type);

};
