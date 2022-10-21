//Name: Alex Reed
//Student ID: G20690958

#include "CJail.h"
#include "CPlayer.h"

//Constructor
CJail::CJail(istream& file) : CSquare(file)
{
	mCost = 50;	//Initialise square cost
	mpJailSquare = this;	//Set mpJailSquare in base class to this square
}

//Return square cost
int CJail::GetCost()
{
	return mCost;
}

//Player lands on square
void CJail::LandOn(CGameManager* pGame, CPlayer* pPlayer)
{
	//Output messages
	cout << pPlayer->GetName() << " lands on " << mName << endl;
	cout << pPlayer->GetName() << " is just visiting" << endl;
}

//Player passes square
void CJail::Pass(CGameManager* pGame, CPlayer* pPlayer)
{

}