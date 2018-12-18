#include "TrexContactListener.h"

#include "cocos2d.h"

#include "GameState.h"

TrexContactListener::TrexContactListener(void)
{
}


TrexContactListener::~TrexContactListener(void)
{
	
}

b2Fixture *TrexContactListener::getFix(b2Fixture *fix){

	auto ud = (cocos2d::CCString *) fix->GetUserData();

	if (ud && ud->compare(GAME_STATE->armsTag) == 0 ){
		return fix;
	}
	else{
		return NULL;
	}
}

void TrexContactListener::BeginContact(b2Contact *contact){

	auto fixA = contact->GetFixtureA();
	auto fixB = contact->GetFixtureB();

	fixA = getFix(fixA);
	fixB = getFix(fixB);

	if (fixA || fixB){
		GAME_STATE->contactCount++;
		cout<<"Pushing"<<GAME_STATE->contactCount<<endl;
		GAME_STATE->pushingFixture = fixA ? fixA : fixB;
		GAME_STATE->pushingNormal = contact->GetManifold()->localNormal;
		GAME_STATE->pushingNormal.Normalize();
	}
}

void TrexContactListener::EndContact(b2Contact *contact){

	auto fixA = contact->GetFixtureA();
	auto fixB = contact->GetFixtureB();

	fixA = getFix(fixA);
	fixB = getFix(fixB);

	if (fixA || fixB){
		GAME_STATE->contactCount--;
		cout<<"Pushing"<<GAME_STATE->contactCount<<endl;
		//if (GAME_STATE->contactCount <= 0){
		//	GAME_STATE->pushingFixture = NULL;
		//}
	}
}