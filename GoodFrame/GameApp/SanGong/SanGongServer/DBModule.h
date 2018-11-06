#pragma once

#include "IDbAnyGame.h"
#include "DB_Connection.h"
#include "DBQuery.h"
#include "RoomInfo.h"

class CDBModule : public IDbAnyGame
{
public:
	CDBModule(void);
	~CDBModule(void);

};

