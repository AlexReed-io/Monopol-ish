//Name: Alex Reed
//Student ID: G20690958

#pragma once

#include <iostream>
#include <memory>
#include "Globals.h"
using namespace std;

class CGameManager;
class CPlayer;

class CSquare
{
protected:
	string mName;	//Square name

	unique_ptr <CSquare> mpNext;	//Pointer to next CSquare in list
	CSquare* mpJailSquare;	//Pointer to Jail square
public:
	CSquare(istream& file);	//Constructor
	virtual ~CSquare();	//Virtual destructor

	string GetName();	//Return square name
	virtual int GetCost();	//Return square cost
	virtual int GetGroup();	//Return square group
	CSquare* GetNext();	//Return pointer to next CSquare in list
	CSquare* GetJailSquare();	//Return pointer to Jail square

	virtual void SetTotalPropertiesInGroup(int total);	//Set mTotalPropertiesInGroup to input amount
	void SetNext(unique_ptr <CSquare> pNext);	//Move input pointer to mpNext
	virtual void LandOn(CGameManager* pGame, CPlayer* pPlayer) = 0;	//Player lands on square (abstract)
	virtual void Pass(CGameManager* pGame, CPlayer* pPlayer) = 0;	//Player passes square (abstract)
	
	friend istream& operator >> (istream& inputStream, CSquare& square);	//Set >> to read in name from file
};