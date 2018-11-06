/*pgeRippleSprite.cpp*/

//
//  pgeRippleSprite.m
//  rippleDemo
//
//  Created by Lars Birkemose on 02/12/11.
//  Copyright 2011 Protec Electronics. All rights reserved.
//


// porting to cplusplus by wanghong.li (wanghong.li1029@163.com)on 04/01/12
// All rights reserved
// --------------------------------------------------------------------------
// include headers


#include "pgeRippleSprite.h"


// --------------------------------------------------------------------------
// implementation


using namespace cocos2d;


CCpgeRippleSprite* CCpgeRippleSprite::rippleSpriteWithFile(const char* filename)
{
	CCpgeRippleSprite* pgeRippleSprite = new CCpgeRippleSprite();
	if(pgeRippleSprite && pgeRippleSprite->initWithFile(filename))
	{
		pgeRippleSprite->autorelease();
		return pgeRippleSprite;
	}


	CC_SAFE_DELETE(pgeRippleSprite);
	return NULL;
}


CCpgeRippleSprite::CCpgeRippleSprite()
:m_texture(NULL),
m_vertice(NULL),
m_textureCoordinate(NULL),
m_rippleCoordinate(NULL),
m_edgeVertice(NULL)
{


}


CCpgeRippleSprite::~CCpgeRippleSprite()
{
	CC_SAFE_RELEASE(m_texture);
	CC_SAFE_DELETE_ARRAY(m_vertice);
	CC_SAFE_DELETE_ARRAY(m_textureCoordinate);
	CC_SAFE_DELETE_ARRAY(m_rippleCoordinate);
	CC_SAFE_DELETE_ARRAY(m_edgeVertice);


	RIPPLE_DATA_LIST iterBegin = m_rippleList.begin();


	while (iterBegin != m_rippleList.end())
	{
		rippleData* date = *iterBegin;


		CC_SAFE_DELETE(date);



		iterBegin++;
	}
	m_rippleList.clear();
}


bool CCpgeRippleSprite::initWithFile(const char* filename)
{
	m_texture = CCTextureCache::sharedTextureCache()->addImage(filename);
	if (!m_texture)
	{
		return false;
	}
	m_texture->retain();


	m_vertice = NULL;
	m_textureCoordinate = NULL;
	CC_SAFE_DELETE_ARRAY(m_vertice);
	CC_SAFE_DELETE_ARRAY(m_textureCoordinate);
	CC_SAFE_DELETE_ARRAY(m_rippleCoordinate);
	CC_SAFE_DELETE_ARRAY(m_edgeVertice);
	m_quadCountX = RIPPLE_DEFAULT_QUAD_COUNT_X;
	m_quadCountY = RIPPLE_DEFAULT_QUAD_COUNT_Y;

	tesselate();

	schedule(schedule_selector(CCpgeRippleSprite::update));

	return true;
}


void CCpgeRippleSprite::draw()
{
	if (false == isVisible())
	{
		return;
	}

	glPushMatrix();

	glDisableClientState(GL_COLOR_ARRAY);

	glBindTexture(GL_TEXTURE_2D, m_texture->getName());

	glTexCoordPointer(2, GL_FLOAT, 0, (m_rippleList.size() == 0) ? m_textureCoordinate : m_rippleCoordinate);

	glVertexPointer(2, GL_FLOAT, 0, m_vertice);

	for (int strip = 0; strip < m_quadCountY; strip++)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, strip * m_VerticesPrStrip, m_VerticesPrStrip);
	}

	glEnableClientState( GL_COLOR_ARRAY );

	// restore
	glPopMatrix( );
}


void CCpgeRippleSprite::tesselate()
{
	int vertexPos = 0;
	CCPoint normalized;


	CC_SAFE_DELETE_ARRAY(m_vertice);
	CC_SAFE_DELETE_ARRAY(m_textureCoordinate);
	CC_SAFE_DELETE_ARRAY(m_rippleCoordinate);
	CC_SAFE_DELETE_ARRAY(m_edgeVertice);


	m_VerticesPrStrip = 2 * (m_quadCountX + 1);
	m_bufferSize = m_VerticesPrStrip * m_quadCountY;


	//allocate buffers


	m_vertice = new CCPoint[m_bufferSize];
	m_textureCoordinate = new CCPoint[m_bufferSize];
	m_rippleCoordinate  = new CCPoint[m_bufferSize];
	m_edgeVertice = new bool[m_bufferSize];


	vertexPos = 0;


	for (int y = 0; y < m_quadCountY; y++)
	{
		for (int x = 0; x < (m_quadCountX + 1); x++)
		{
			for ( int yy = 0; yy < 2; yy ++ ) {


				// first simply calculate a normalized position into rectangle
				normalized.x = ( float )x / ( float )m_quadCountX;
				normalized.y = ( float )( y + yy ) / ( float )m_quadCountY;


				// calculate vertex by multiplying rectangle ( texture ) size
				CCSize contentSize = m_texture->getContentSize();
				m_vertice[ vertexPos ] = ccp( normalized.x * contentSize.width, normalized.y * contentSize.height);


				// adjust texture coordinates according to texture size
				// as a texture is always in the power of 2, maxS and maxT are the fragment of the size actually used
				// invert y on texture coordinates
				m_textureCoordinate[ vertexPos ] = ccp( normalized.x * m_texture->getMaxS(), m_texture->getMaxT()- ( normalized.y * m_texture->getMaxT() ) );


				// check if vertice is an edge vertice, because edge vertices are never modified to keep outline consistent
				m_edgeVertice[ vertexPos ] = ( 
					( x == 0 ) || 
					( x == m_quadCountX ) ||
					( ( y == 0 ) && ( yy == 0 ) ) || 
					( ( y == ( m_quadCountY - 1 ) ) && ( yy > 0 ) ) );


				// next buffer pos
				vertexPos ++;


			}
		}
	}
}


void CCpgeRippleSprite::addRipple(cocos2d::CCPoint &pos, RIPPLE_TYPE type, float strength)
{
	rippleData* newRipple;


	// allocate new ripple
	newRipple = new rippleData;


	// initialize ripple
	newRipple->parent = true;
	for ( int count = 0; count < 4; count ++ ) newRipple->childCreated[ count ] = false;
	newRipple->rippleType = type;
	newRipple->center = pos;


	CCSize contentSize = m_texture->getContentSize();
	newRipple->centerCoordinate = ccp( pos.x / contentSize.width * m_texture->getMaxS(), m_texture->getMaxT() - ( pos.y / contentSize.height * m_texture->getMaxT()) );
	newRipple->radius = RIPPLE_DEFAULT_RADIUS; // * strength;
	newRipple->strength = strength;
	newRipple->runtime = 0;
	newRipple->currentRadius = 0;
	newRipple->rippleCycle = RIPPLE_DEFAULT_RIPPLE_CYCLE;
	newRipple->lifespan = RIPPLE_DEFAULT_LIFESPAN;


	// add ripple to running list 
	m_rippleList.push_back(newRipple);
}


void CCpgeRippleSprite::addRippleChild(rippleData* parent, RIPPLE_CHILD type)
{
	rippleData* newRipple;
	CCPoint pos;


	// allocate new ripple
	newRipple = new rippleData;


	// new ripple is pretty much a copy of its parent
	memcpy( newRipple, parent, sizeof( rippleData ) );


	// not a parent
	newRipple->parent = false;


	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	// mirror position
	switch ( type ) {
		case RIPPLE_CHILD_LEFT:
			pos = ccp( -parent->center.x, parent->center.y );
			break;
		case RIPPLE_CHILD_TOP:
			pos = ccp( parent->center.x, winSize.height + ( winSize.height - parent->center.y ) );
			break;
		case RIPPLE_CHILD_RIGHT:
			pos = ccp( winSize.width + ( winSize.width - parent->center.x ), parent->center.y );            
			break;
		case RIPPLE_CHILD_BOTTOM:
		default:
			pos = ccp( parent->center.x, -parent->center.y );            
			break;
	}


	newRipple->center = pos;


	CCSize contentSize = m_texture->getContentSize();


	newRipple->centerCoordinate = ccp( pos.x / contentSize.width * m_texture->getMaxS(), m_texture->getMaxT()- ( pos.y / contentSize.height * m_texture->getMaxT()) );
	newRipple->strength *= RIPPLE_CHILD_MODIFIER;


	// indicate child used
	parent->childCreated[ type ] = true;        


	// add ripple to running list 
	m_rippleList.push_back(newRipple);
}


void CCpgeRippleSprite::update(float dt)
{
	rippleData* ripple;
	CCPoint pos;
	float distance, correction;


	// test if any ripples at all
	if ( m_rippleList.size() == 0 ) return;


	// ripples are simulated by altering texture coordinates
	// on all updates, an entire new array is calculated from the base array 
	// not maintainng an original set of texture coordinates, could result in accumulated errors
	memcpy( m_rippleCoordinate, m_textureCoordinate, m_bufferSize * sizeof( CCPoint ) );


	// scan through running ripples
	// the scan is backwards, so that ripples can be removed on the fly


	CCSize winSize = CCDirector::sharedDirector()->getWinSize();


	REVERSE_RIPPLE_DATA_LIST iterRipple = m_rippleList.rbegin();


	while (  iterRipple != m_rippleList.rend()) 
	{


		// get ripple data
		ripple = *iterRipple;


		// scan through all texture coordinates
		for ( int count = 0; count < m_bufferSize; count ++ ) {


			// dont modify edge vertices
			if ( m_edgeVertice[ count ] == false ) {


				// calculate distance
				// you might think it would be faster to do a box check first
				// but it really isnt, 
				// ccpDistance is like my sexlife - BAM! - and its all over
				distance = ccpDistance( ripple->center, m_vertice[ count ] );


				// only modify vertices within range
				if ( distance <= ripple->currentRadius ) {


					// load the texture coordinate into an easy to use var
					pos = m_rippleCoordinate[ count ];  


					// calculate a ripple 
					switch ( ripple->rippleType ) {


						case RIPPLE_TYPE_RUBBER:
							// method A
							// calculate a sinus, based only on time
							// this will make the ripples look like poking a soft rubber sheet, since sinus position is fixed
							correction = sinf( 2 * M_PI * ripple->runtime / ripple->rippleCycle );
							break;


						case RIPPLE_TYPE_GEL:
							// method B
							// calculate a sinus, based both on time and distance
							// this will look more like a high viscosity fluid, since sinus will travel with radius                            
							correction = sinf( 2 * M_PI * ( ripple->currentRadius - distance ) / ripple->radius * ripple->lifespan / ripple->rippleCycle );
							break;


						case RIPPLE_TYPE_WATER:
						default:
							// method c
							// like method b, but faded for time and distance to center
							// this will look more like a low viscosity fluid, like water     


							correction = ( ripple->radius * ripple->rippleCycle / ripple->lifespan ) / ( ripple->currentRadius - distance );
							if ( correction > 1.0f ) correction = 1.0f;


							// fade center of quicker
							correction *= correction;


							correction *= sinf( 2 * M_PI * ( ripple->currentRadius - distance ) / ripple->radius * ripple->lifespan / ripple->rippleCycle );
							break;


					}


					// fade with distance
					correction *= 1 - ( distance / ripple->currentRadius );


					// fade with time
					correction *= 1 - ( ripple->runtime / ripple->lifespan );


					// adjust for base gain and user strength
					correction *= RIPPLE_BASE_GAIN;
					correction *= ripple->strength;


					// finally modify the coordinate by interpolating
					// because of interpolation, adjustment for distance is needed, 
					correction /= ccpDistance( ripple->centerCoordinate, pos );
					pos = ccpAdd( pos, ccpMult( ccpSub( pos, ripple->centerCoordinate ), correction ) );


					// another approach for applying correction, would be to calculate slope from center to pos
					// and then adjust based on this


					// clamp texture coordinates to avoid artifacts
					pos = ccpClamp( pos, CCPointZero, ccp( m_texture->getMaxS(), m_texture->getMaxT()) );


					// save modified coordinate
					m_rippleCoordinate[ count ] = pos;


				}
			}
		}


		// calculate radius
		ripple->currentRadius = ripple->radius * ripple->runtime / ripple->lifespan;


		// check if ripple should expire
		ripple->runtime += dt;
		if ( ripple->runtime >= ripple->lifespan )
		{
			// free memory, and remove from list
			CC_SAFE_DELETE( ripple );


			RIPPLE_DATA_LIST it = --iterRipple.base() ;  
			RIPPLE_DATA_LIST it_after_del = m_rippleList.erase(it); 
			iterRipple = std::list<rippleData*>::reverse_iterator(it_after_del); 
		} 
		else
		{
			// check for creation of child ripples
			if ( ripple->parent == true ) {


				// left ripple
				if ( ( ripple->childCreated[ RIPPLE_CHILD_LEFT ] == false ) && ( ripple->currentRadius > ripple->center.x ) ) {
					addRippleChild(ripple, RIPPLE_CHILD_LEFT);
				} 


				// top ripple
				if ( ( ripple->childCreated[ RIPPLE_CHILD_TOP ] == false ) && ( ripple->currentRadius > winSize.height - ripple->center.y ) ) {
					addRippleChild(ripple, RIPPLE_CHILD_TOP);
				}


				// right ripple
				if ( ( ripple->childCreated[ RIPPLE_CHILD_RIGHT ] == false ) && ( ripple->currentRadius > winSize.width - ripple->center.x ) ) {
					addRippleChild(ripple, RIPPLE_CHILD_RIGHT);
				}


				// bottom ripple
				if ( ( ripple->childCreated[ RIPPLE_CHILD_BOTTOM ] == false ) && ( ripple->currentRadius > ripple->center.y ) ) {
					addRippleChild(ripple, RIPPLE_CHILD_BOTTOM);
				} 
			}
			iterRipple++;
		}
	}
}
