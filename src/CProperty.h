//Name: Alex Reed
//Student ID: G20690958

#pragma once

#include "CSquare.h"

class CProperty :
    public CSquare
{
protected:
	int mCost;	//Property cost
	int mRent;	//Property rent
	int mGroup;	//Property group
	string mColour;	//Property colour
	int mTotalPropertiesInGroup;	//Total number of properties in group
	bool mMortgaged;	//Flag to show if mortgaged

	CPlayer* mpOwner;	//Pointer to CPlayer owner of property
public:
	CProperty(istream& file);	//Constructor

	int GetCost();	//Return property cost
	int GetRent();	//Return property rent
	int GetGroup();	//Return property group
	string GetColour();	//Return property colour
	int GetTotalPropertiesInGroup();	//Return total number of properties in group
	bool GetMortgaged();	//Return flag for if mortgaged
	CPlayer* GetOwner();	//Return pointer to CPlayer owner of property

	void SetRent(int rent);	//Set mRent to input amount
	void SetTotalPropertiesInGroup(int total);	//Set mTotalPropertiesInGroup to input amount
	void SetMortgaged(bool mortgaged);	//Set mMortgaged to input bool
	void SetOwner(CPlayer* pPlayer);	//Set mpOwner to input CPlayer pointer
	virtual void LandOn(CGameManager* pGame, CPlayer* pPlayer);	//Player lands on square
	virtual void Pass(CGameManager* pGame, CPlayer* pPlayer);	//Player passes square
	
	friend istream& operator >> (istream& inputStream, CProperty& property);	//Set >> to read in cost, rent, and group from file
};