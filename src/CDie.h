//Name: Alex Reed
//Student ID: G20690958

#pragma once

#include <iostream>
#include <fstream>
using namespace std;

class CPlayer;

class CDie
{
protected:
	int mSeed;	//Seed value
public:
	CDie();	//Constructor
	
	int Roll(CPlayer* pPlayer);	//Return next die roll number for input player
};
