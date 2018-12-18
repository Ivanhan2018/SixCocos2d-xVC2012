#pragma once

#include <Box2D.h>

#define GAME_STATE (GameState::singleton())

class GameState
{
private:
	GameState(void);
	~GameState(void);

	static GameState *_singleton;

public:

	static GameState *singleton();

	static void reset();

	void update(float dt);

	// Members
	int contactCount;

	char *armsTag;

	float pushForce;

	b2Fixture *pushingFixture;

	b2Vec2 pushingNormal;
};

