//Name: Alex Reed
//Student ID: G20690958

#pragma once

#include "CSquare.h"

class CGoToJail :
    public CSquare
{
public:
	CGoToJail(istream& file, CSquare* pJailSquare);	//Constructor

	virtual void LandOn(CGameManager* pGame, CPlayer* pPlayer);	//Player lands on square
	virtual void Pass(CGameManager* pGame, CPlayer* pPlayer);	//Player passes square
};
