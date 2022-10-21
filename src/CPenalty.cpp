//Name: Alex Reed
//Student ID: G20690958

#include "CPenalty.h"
#include "CGameManager.h"
#include "CDie.h"
#include "CPlayer.h"

//Constructor
CPenalty::CPenalty(istream& file) : CSquare(file)
{
	
}

//Player lands on square
void CPenalty::LandOn(CGameManager* pGame, CPlayer* pPlayer)
{
	cout << pPlayer->GetName() << " lands on " << mName << endl;	//Output lands on message

	CDie* pDie = pGame->GetDiePtr();	//Get pointer to CDie class
	int dieRoll = pDie->Roll(pPlayer);	//Roll die for player
	string penaltyMessage = "";	//Penalty message for output
	int penaltyAmount = 0;	//Penalty amount

	//Use die roll and set penalty message and amount accordingly
	switch (dieRoll)
	{
	case 1:
	{
		penaltyMessage = "Buy a coffee in Starbucks";
		penaltyAmount = 20;
		break;
	}
	case 2:
	{
		penaltyMessage = "Pay your broadband bill";
		penaltyAmount = 50;
		break;
	}
	case 3:
	{
		penaltyMessage = "Visit the SU shop for food";
		penaltyAmount = 100;
		break;
	}
	case 4:
	{
		penaltyMessage = "Buy an assignment solution";
		penaltyAmount = 150;
		break;
	}
	case 5:
	{
		penaltyMessage = "Go for a romantic meal";
		penaltyAmount = 200;
		break;
	}
	case 6:
	{
		penaltyMessage = "Pay some university fees";
		penaltyAmount = 300;
		break;
	}
	default:
	{

	}
	}

	cout << penaltyMessage << ". Lose " << POUND << penaltyAmount << endl;	//Output penalty message

	pPlayer->DecreaseBalance(penaltyAmount);	//Decrease player's balance by penalty amount
}

//Player passes square
void CPenalty::Pass(CGameManager* pGame, CPlayer* pPlayer)
{

}