//Name: Alex Reed
//Student ID: G20690958

#pragma once

#include <memory>
#include "CPlayer.h"
using namespace std;

class CGameManager;

class CPlayersList
{
protected:
	unique_ptr <CPlayer> mpHead;	//Pointer to first CPlayer in list
public:
	CPlayersList();	//Constructor

	CPlayer* GetHead();	//Return pointer to first CPlayer in list
	CPlayer* GetFirstSolventPlayer();	//Return pointer to first solvent CPlayer in list
	CPlayer* GetNextSolventPlayer(CPlayer* pCurrentPlayer);	//Return pointer to next solvent CPlayer in list
	int CountSolventPlayers();	//Return number of solvent players in list

	void NewPlayer(string name, CGameManager* pGame);	//Create new CPlayer and add to list
	void PushBack(unique_ptr <CPlayer> pNewPlayer);	//Push input pointer to CPlayer to back of list
};

