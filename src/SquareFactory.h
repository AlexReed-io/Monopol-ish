//Name: Alex Reed
//Student ID: G20690958

#pragma once

#include "CSquare.h"

//Convert input integer to square type
enum class ESquareType : int
{
	property = 1,
	go = 2,
	station = 3,
	bonus = 4,
	penalty = 5,
	jail = 6,
	goToJail = 7,
	freeParking = 8
};

unique_ptr <CSquare> NewSquare(ESquareType square, istream& file, CSquare* pJailSquare);	//Create and return pointer to new CSquare