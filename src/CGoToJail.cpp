//Name: Alex Reed
//Student ID: G20690958

#include "CGoToJail.h"
#include "CPlayer.h"
#include "CGameManager.h"

//Constructor
CGoToJail::CGoToJail(istream& file, CSquare* pJailSquare) : CSquare(file)
{
	mpJailSquare = pJailSquare;	//Assign Jail square pointer to pointer
}

//Player lands on square
void CGoToJail::LandOn(CGameManager* pGame, CPlayer* pPlayer)
{
	pPlayer->SetPosition(mpJailSquare);	//Move player to Jail square
	pPlayer->DecreaseBalance(mpJailSquare->GetCost());	//Decrease player's balance by Jail square cost
	
	//Output messages
	cout << pPlayer->GetName() << " lands on " << mName << endl;
	cout << pPlayer->GetName() << " goes to Jail" << endl;
	cout << pPlayer->GetName() << " pays " << POUND << mpJailSquare->GetCost() << endl;
}

//Player passes square
void CGoToJail::Pass(CGameManager* pGame, CPlayer* pPlayer)
{

}