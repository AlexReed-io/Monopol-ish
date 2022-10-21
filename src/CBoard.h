//Name: Alex Reed
//Student ID: G20690958

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>
#include "SquareFactory.h"
#include "SColourGroup.h"
using namespace std;

using colourGroups = vector<SColourGroup>;
using colourGroupsIter = vector<SColourGroup>::iterator;

class CBoard
{
protected:
	bool mSquaresCreated;	//Flag to show if squares successfully created
	unique_ptr <CSquare> mpHead;	//Pointer to first CSquare in list
	colourGroups mColourGroups;	//Vector to hold colour groups and totals
	CSquare* mpJailSquare;	//Pointer to Jail square
public:
	CBoard();	//Constructor
	
	bool GetSquaresCreated();	//Return flag for if squares created
	CSquare* GetHead();	//Return pointer to first CSquare in list
	CSquare* GetNextSquare(CSquare* pCurrentSquare);	//Return pointer to next CSquare in list, looping back to start
	CSquare* GetJailSquare();	//Return pointer to Jail square

	void PushBack(unique_ptr <CSquare> pNewSquare);	//Push input pointer to CSquare to back of list
	void AddColourGroup(CSquare* pNewSquare);	//Add input CSquare group to mColourGroups vector
	void AddGroupTotalsToProperties();	//Add total squares in colour group from mColourGroups vector to each property
	void CreateSquares();	//Read in text file to create squares
};

