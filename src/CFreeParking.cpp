//Name: Alex Reed
//Student ID: G20690958

#include "CFreeParking.h"
#include "CPlayer.h"

//Constructor
CFreeParking::CFreeParking(istream& file) : CSquare(file)
{
	
}

//Player lands on square
void CFreeParking::LandOn(CGameManager* pGame, CPlayer* pPlayer)
{
	//Output messages
	cout << pPlayer->GetName() << " lands on " << mName << endl;
	cout << pPlayer->GetName() << " is resting" << endl;
}

//Player passes square
void CFreeParking::Pass(CGameManager* pGame, CPlayer* pPlayer)
{

}