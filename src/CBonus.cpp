//Name: Alex Reed
//Student ID: G20690958

#include "CBonus.h"
#include "CGameManager.h"
#include "CBank.h"
#include "CDie.h"
#include "CPlayer.h"

//Constructor
CBonus::CBonus(istream& file) : CSquare(file)
{
	
}

//Player lands on square
void CBonus::LandOn(CGameManager* pGame, CPlayer* pPlayer)
{
	cout << pPlayer->GetName() << " lands on " << mName << endl;	//Output lands on message

	CBank* pBank = pGame->GetBankPtr();	//Get pointer to CBank class
	CDie* pDie = pGame->GetDiePtr();	//Get pointer to CDie class
	int dieRoll = pDie->Roll(pPlayer);	//Roll die for player
	string bonusMessage = "";	//Bonus message for output
	int bonusAmount = 0;	//Bonus amount
	
	//Use die roll and set bonus message and amount accordingly
	switch (dieRoll)
	{
	case 1:
	{
		bonusMessage = "Find some money";
		bonusAmount = 20;
		break;
	}
	case 2:
	{
		bonusMessage = "Win a coding competition";
		bonusAmount = 50;
		break;
	}
	case 3:
	{
		bonusMessage = "Receive a rent rebate";
		bonusAmount = 100;
		break;
	}
	case 4:
	{
		bonusMessage = "Win the lottery";
		bonusAmount = 150;
		break;
	}
	case 5:
	{
		bonusMessage = "Sell your iPad";
		bonusAmount = 200;
		break;
	}
	case 6:
	{
		bonusMessage = "It's your birthday";
		bonusAmount = 300;
		break;
	}
	default:
	{

	}
	}

	//If bank can afford bonus then run
	if (pBank->GetBalance() >= bonusAmount)
	{
		cout << bonusMessage << ". Gain " << POUND << bonusAmount << endl;	//Output bonus message
		
		pPlayer->IncreaseBalance(bonusAmount);	//Increase player's balance by bonus amount
	}
	else
	{
		cout << "Bank does not have sufficient funds to pay " << pPlayer->GetName() << " the bonus" << endl;
	}
}

//Player passes square
void CBonus::Pass(CGameManager* pGame, CPlayer* pPlayer)
{

}