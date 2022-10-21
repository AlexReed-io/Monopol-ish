//Name: Alex Reed
//Student ID: G20690958

#include "CStation.h"
#include "CGameManager.h"
#include "CBank.h"
#include "CPlayer.h"

//Constructor
CStation::CStation(istream& file) : CSquare(file)
{
	mCost = 200;	//Initialise station cost
	mRent = 10;	//Initialise station rent
	mpOwner = nullptr;	//Initialise pointer to CPlayer owner of station
}

//Return station cost
int CStation::GetCost()
{
	return mCost;
}

//Set mpOwner to input CPlayer pointer
void CStation::SetOwner(CPlayer* pPlayer)
{
	mpOwner = pPlayer;
}

//Player lands on square
void CStation::LandOn(CGameManager* pGame, CPlayer* pPlayer)
{
	cout << pPlayer->GetName() << " lands on " << mName << endl;	//Output lands on message

	CBank* pBank = pGame->GetBankPtr();	//Get pointer to CBank class

	//If station is not owned, player buys station
	//Else, if player is not owner then player pays owner for ticket
	if (mpOwner == nullptr)
	{
		cout << pPlayer->GetName() << " buys " << mName << " for " << POUND << mCost << endl;	//Output message

		pPlayer->BuyStation(this);	//Player buys station
	}
	else if (mpOwner != pPlayer)
	{
		cout << pPlayer->GetName() << " pays " << POUND << mRent << " for ticket" << endl;	//Output message
		
		pPlayer->PayRent(mRent, mpOwner);	//Pay rent amount from player to owner
	}
}

//Player passes square
void CStation::Pass(CGameManager* pGame, CPlayer* pPlayer)
{

}