//Name: Alex Reed
//Student ID: G20690958

#include "SquareFactory.h"
#include "CProperty.h"
#include "CGo.h"
#include "CStation.h"
#include "CBonus.h"
#include "CPenalty.h"
#include "CJail.h"
#include "CGoToJail.h"
#include "CFreeParking.h"

//Create and return pointer to new CSquare
unique_ptr <CSquare> NewSquare(ESquareType square, istream& file, CSquare* pJailSquare)
{
	unique_ptr <CSquare> pSquare = nullptr;	//Create null pointer to CSquare class

	//Use square type to create relevant pointer to
	//derived class with input file passed in
	switch (square)
	{
	case ESquareType::property:
	{
		pSquare = make_unique<CProperty>(file);
		break;
	}
	case ESquareType::go:
	{
		pSquare = make_unique<CGo>(file);
		break;
	}
	case ESquareType::station:
	{
		pSquare = make_unique<CStation>(file);
		break;
	}
	case ESquareType::bonus:
	{
		pSquare = make_unique<CBonus>(file);
		break;
	}
	case ESquareType::penalty:
	{
		pSquare = make_unique<CPenalty>(file);
		break;
	}
	case ESquareType::jail:
	{
		pSquare = make_unique<CJail>(file);
		break;
	}
	case ESquareType::goToJail:
	{
		pSquare = make_unique<CGoToJail>(file, pJailSquare);	//Also pass in pointer to Jail square
		break;
	}
	case ESquareType::freeParking:
	{
		pSquare = make_unique<CFreeParking>(file);
		break;
	}
	default:
	{

	}
	return move(pSquare);
	}

	return move(pSquare);
}