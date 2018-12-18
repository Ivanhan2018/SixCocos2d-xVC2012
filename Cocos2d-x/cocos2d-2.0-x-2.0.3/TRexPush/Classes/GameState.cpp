#include "GameState.h"

#include <cstdlib>
#include <iostream>

using namespace std;

GameState::GameState(void)
{
	contactCount = 0;
	armsTag = "Arms";
	pushForce = 1000;
	pushingFixture = NULL;
	pushingNormal = b2Vec2_zero;
}


GameState::~GameState(void)
{
}

GameState *GameState::_singleton = NULL;
GameState *GameState::singleton(){

	return _singleton;
}

void GameState::reset(){

	delete _singleton;

	_singleton = new GameState();
}

void GameState::update(float dt){

	//TODO: Apply only once?
	static int lastCount = 0;
	if (lastCount == 0 && contactCount > 0 && pushingFixture){
		lastCount = contactCount;
		auto v = pushingNormal;
		v *= pushForce;
		cout<<"Pushing"<<endl;
		pushingFixture->GetBody()->ApplyForceToCenter(v);
	}

}