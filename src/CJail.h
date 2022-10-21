//Name: Alex Reed
//Student ID: G20690958

#pragma once

#include "CSquare.h"

class CJail :
    public CSquare
{
protected:
	int mCost;	//Square cost
public:
	CJail(istream& file);	//Constructor

	int GetCost();	//Return square cost

	virtual void LandOn(CGameManager* pGame, CPlayer* pPlayer);	//Player lands on square
	virtual void Pass(CGameManager* pGame, CPlayer* pPlayer);	//Player passes square
};

