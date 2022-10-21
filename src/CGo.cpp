//Name: Alex Reed
//Student ID: G20690958

#include "CGo.h"
#include "CGameManager.h"
#include "CBank.h"
#include "CPlayer.h"

//Constructor
CGo::CGo(istream& file) : CSquare(file)
{
	mBonus = 200;	//Initalise square bonus
}

//Player lands on square
void CGo::LandOn(CGameManager* pGame, CPlayer* pPlayer)
{
	CBank* pBank = pGame->GetBankPtr();	//Get pointer to CBank class
	
	//If bank can afford bonus then add it to player's balance
	if (pBank->GetBalance() >= mBonus)
	{
		cout << pPlayer->GetName() << " lands on " << mName << " and collects " << POUND << mBonus << endl;	//Output message
		
		pPlayer->IncreaseBalance(mBonus);	//Add bonus to player's balance
	}
	else
	{
		//Ouput messages
		cout << pPlayer->GetName() << " lands on " << mName << endl;
		cout << "Bank does not have sufficient funds to pay " << pPlayer->GetName() << " for landing on " << mName << endl;
	}
}

//Player passes square
void CGo::Pass(CGameManager* pGame, CPlayer* pPlayer)
{
	CBank* pBank = pGame->GetBankPtr();	//Get pointer to CBank class
	
	//If bank can afford bonus then add it to player's balance
	if (pBank->GetBalance() >= mBonus)
	{
		cout << pPlayer->GetName() << " passes " << mName << " and collects " << POUND << mBonus << endl;	//Output message
		
		pPlayer->IncreaseBalance(mBonus);	//Add bonus to player's balance
	}
	else
	{
		//Ouput messages
		cout << pPlayer->GetName() << " passes " << mName << endl;
		cout << "Bank does not have sufficient funds to pay " << pPlayer->GetName() << " for passing " << mName << endl;
	}
}