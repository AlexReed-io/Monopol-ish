//Name: Alex Reed
//Student ID: G20690958

#pragma once

#include "CSquare.h"

class CPenalty :
    public CSquare
{
public:
	CPenalty(istream& file);	//Constructor

	virtual void LandOn(CGameManager* pGame, CPlayer* pPlayer);	//Player lands on square
	virtual void Pass(CGameManager* pGame, CPlayer* pPlayer);	//Player passes square
};

