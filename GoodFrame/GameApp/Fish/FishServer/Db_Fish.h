#pragma once

#include "IDbAnyGame.h"
#include "./DB_Connection.h"
#include "./DBQuery_Fish.h"

class CDb_Fish : public IDbAnyGame
{
public:
	CDb_Fish(void);
	~CDb_Fish(void);
};

