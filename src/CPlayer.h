//Name: Alex Reed
//Student ID: G20690958

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "Globals.h"
using namespace std;

class CGameManager;
class CBank;
class CSquare;
class CProperty;
class CStation;

using ownedProperties = vector<CProperty*>;
using ownedPropertiesIter = vector<CProperty*>::iterator;
using ownedStations = vector<CStation*>;
using ownedStationsIter = vector<CStation*>::iterator;

class CPlayer
{
protected:
	string mName;	//Player's name
	int mBalance;	//Player's current balance
	CSquare* mpPosition;	//Pointer to player's position
	bool mSolvent;	//Flag to show if player is solvent
	ownedProperties mOwnedProperties;	//Vector of pointers to owned CProperty squares
	ownedStations mOwnedStations;	//Vector of pointers to owned CStation squares

	unique_ptr <CPlayer> mpNext;	//Pointer to next CPlayer in list
	CBank* mpBank;	//Pointer to CBank class

	CProperty* GetCheapestProperty();	//Return pointer to cheapest owned property
	CProperty* GetCheapestMortgagedProperty();	//Return pointer to cheapest mortgaged property
	void SortOwnedPropertiesByCost();	//Sort mOwnedProperties vector by property cost in ascending value
	void MortgageCheapestProperty();	//Mortgage cheapest property
	void BuyBackCheapestMortgaged();	//Buy back cheapest mortgaged property
public:
	CPlayer(string name, CGameManager* pGame);	//Constructor

	string GetName();	//Return player's name
	int GetBalance();	//Return player's current balance
	CSquare* GetPosition();	//Return pointer to player's position
	bool GetSolvent();	//Return flag for if player is solvent
	CPlayer* GetNext();	//Return pointer to next CPlayer in list

	void DisplayBalance();	//Output player's current balance
	void IncreaseBalance(int amount);	//Increase player's balance and decrease bank balance by input amount
	void DecreaseBalance(int amount);	//Decrease player's balance and increase bank balance by input amount
	void ReceiveRent(int amount);	//Increase player's balance by input amount
	void PayRent(int amount, CPlayer* pOwner);	//Pay input amount to input CPlayer
	void SetPosition(CSquare* pSquare);	//Set player's position to input pointer
	void BuyProperty(CProperty* pProperty);	//Buy input property
	void BuyStation(CStation* pStation);	//Buy input station
	void SetNext(unique_ptr <CPlayer> pNext);	//Move input pointer to mpNext
};

bool compareCosts(CProperty* pProperty1, CProperty* pProperty2);	//Compare costs of input pointers