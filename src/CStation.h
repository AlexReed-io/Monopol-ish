//Name: Alex Reed
//Student ID: G20690958

#pragma once

#include "CSquare.h"

class CStation :
    public CSquare
{
protected:
	int mCost;	//Station cost
	int mRent;	//Station rent

	CPlayer* mpOwner;	//Pointer to CPlayer owner of station
public:
	CStation(istream& file);	//Constructor

	int GetCost();	//Return station cost

	void SetOwner(CPlayer* pPlayer);	//Set mpOwner to input CPlayer pointer
	virtual void LandOn(CGameManager* pGame, CPlayer* pPlayer);	//Player lands on square
	virtual void Pass(CGameManager* pGame, CPlayer* pPlayer);	//Player passes square
};