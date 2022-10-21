//Name: Alex Reed
//Student ID: G20690958

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>
#include "CBank.h"
#include "CDie.h"
#include "CBoard.h"
#include "CPlayersList.h"
using namespace std;

class CGameManager
{
protected:
	int mRound;	//Current round in game
	int mTotalRounds;	//Total number of rounds in game
	bool mEnoughSolventPlayers;	//Flag to check there is more than one solvent player

	unique_ptr <CBank> mpBank;	//Pointer to CBank class
	unique_ptr <CDie> mpDie;	//Pointer to CDie class
	unique_ptr <CBoard> mpBoard;	//Pointer to CBoard class
	unique_ptr <CPlayersList> mpPlayersList;	//Pointer to CPlayersList class
public:
	CGameManager();	//Constructor

	CBank* GetBankPtr();	//Return pointer to CBank class
	CDie* GetDiePtr();	//Return pointer to CDie class
	CBoard* GetBoardPtr();	//Return pointer to CBoard class

	void NewPlayer(string name);	//Create new player with input name
	void PlayGame();	//Play the rounds of the game
	void MovePlayersToStart();	//Move each player to first square in CBoard list
	void PlayRound();	//Play a round
	void TakePlayerTurn(CPlayer* pPlayer);	//Input player takes their turn
	void EndGame();	//Display player totals and winner of game
};

