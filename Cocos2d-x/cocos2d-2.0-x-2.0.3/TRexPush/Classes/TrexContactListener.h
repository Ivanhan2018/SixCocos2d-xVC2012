#pragma once

#include <Box2D.h>

class TrexContactListener : public b2ContactListener
{
private:

	b2Fixture *getFix(b2Fixture *fix);

public:
	TrexContactListener(void);
	~TrexContactListener(void);

	void BeginContact(b2Contact *);
	void EndContact(b2Contact *);
};