//Name: Alex Reed
//Student ID: G20690958

#include "CGameManager.h"
#include "CSquare.h"
#include "SquareFactory.h"
#include "CPlayer.h"

//Constructor
CGameManager::CGameManager()
{
	mRound = 1;	//Set starting round number
	mTotalRounds = 20;	//Set total number of rounds
	mEnoughSolventPlayers = true;	//Initialise solvent players flag
	mpBank = make_unique<CBank>();	//Create pointer to CBank class
	mpDie = make_unique<CDie>();	//Create pointer to CDie class
	mpBoard = make_unique<CBoard>();	//Create pointer to CBoard class
	mpPlayersList = make_unique<CPlayersList>();	//Create pointer to CPlayersList class
}

//Return pointer to CBank class
CBank* CGameManager::GetBankPtr()
{
	return mpBank.get();
}

//Return pointer to CDie class
CDie* CGameManager::GetDiePtr()
{
	return mpDie.get();
}

//Return pointer to CBoard class
CBoard* CGameManager::GetBoardPtr()
{
	return mpBoard.get();
}

//Create new player with input name
void CGameManager::NewPlayer(string name)
{
	mpPlayersList->NewPlayer(name, this);	//Create new player in CPlayersList class
}

//Play the rounds of the game
void CGameManager::PlayGame()
{
	//If board has been created then run
	//Else, output message
	if (mpBoard->GetSquaresCreated())
	{
		//If two or more players then run
		//Else, output message
		if (mpPlayersList->CountSolventPlayers() >= 2)
		{
			cout << "Welcome to Monopol-ish" << endl << endl;
			
			MovePlayersToStart();	//Move each player to first square in CBoard list

			//While there are at least two solvent players,
			//play each round up to total number of rounds
			while (mRound <= mTotalRounds && mEnoughSolventPlayers)
			{
				PlayRound();	//Play a round
			}

			EndGame();	//Display player totals and winner of game
		}
		else
		{
			cout << "There must be at least two players for the game to be played" << endl;
		}
	}
	else
	{
		cout << "Board has not been created so the game cannot be played" << endl;
	}
}

//Move each player to first square in CBoard list
void CGameManager::MovePlayersToStart()
{
	CPlayer* pCurrentPlayer = mpPlayersList->GetHead();	//Get first player

	//Loop through each player in list
	while (pCurrentPlayer)
	{
		pCurrentPlayer->SetPosition(mpBoard->GetHead());	//Set player position to first square in list

		pCurrentPlayer = pCurrentPlayer->GetNext();
	}
}

//Play a round
void CGameManager::PlayRound()
{
	cout << "==========" << endl << endl;	//Output seperator line
	cout << "Round " << mRound << endl << endl;	//Output round number

	CPlayer* pCurrentPlayer = mpPlayersList->GetFirstSolventPlayer();	//Get first solvent player

	//While there at least two solvent players, loop through list of players
	while (pCurrentPlayer && mEnoughSolventPlayers)
	{
		TakePlayerTurn(pCurrentPlayer);	//Player takes their turn

		pCurrentPlayer = mpPlayersList->GetNextSolventPlayer(pCurrentPlayer);	//Get next solvent player
	}

	mRound++;	//Increment round number
}

//Input player takes their turn
void CGameManager::TakePlayerTurn(CPlayer* pPlayer)
{	
	CSquare* pCurrentPosition = pPlayer->GetPosition();	//Get player's current position

	int dieRoll = mpDie->Roll(pPlayer);	//Get next die roll number

	//Move player up to die roll number of times
	for (int i = 1; i <= dieRoll; i++)
	{
		pCurrentPosition = mpBoard->GetNextSquare(pCurrentPosition);	//Set position to next square
		
		//If not the final die roll, run the Pass function
		//If the final die roll, run the LandOn function
		if (i != dieRoll)
		{
			pCurrentPosition->Pass(this, pPlayer);	//Player passes square
		}
		else
		{
			pPlayer->SetPosition(pCurrentPosition);	//Set new position for player
			pCurrentPosition->LandOn(this, pPlayer);	//Player lands on square
		}
	}

	//If player is solvent, output balance
	if (pPlayer->GetSolvent())
	{
		pPlayer->DisplayBalance();
	}

	//If there are not at least two solvent players, set flag to false
	if (mpPlayersList->CountSolventPlayers() < 2)
	{
		mEnoughSolventPlayers = false;
	}

	cout << endl;
}

//Display player totals and winner of game
void CGameManager::EndGame()
{
	cout << "==========" << endl << endl;	//Output seperator line
	cout << "Game Over" << endl;

	//(mpPlayersList->GetHead())->DecreaseBalance(585);
	//((mpPlayersList->GetHead())->GetNext())->IncreaseBalance(660);
	
	CPlayer* pCurrentPlayer = mpPlayersList->GetHead();	//Get first player
	int pHighestBalance = pCurrentPlayer->GetBalance();	//Highest balance starts with first player's balance

	//Loop through players in list
	while (pCurrentPlayer)
	{
		pCurrentPlayer->DisplayBalance();	//Output player balance
		
		//If player's balance is higher than current highest, replace highest
		if (pCurrentPlayer->GetBalance() > pHighestBalance)
		{
			pHighestBalance = pCurrentPlayer->GetBalance();
		}

		pCurrentPlayer = pCurrentPlayer->GetNext();
	}

	cout << endl;

	vector<string> winningPlayers;	//Vector of pointers to winning players
	int countWinningPlayers = 0;	//Number of winning players
	string winningPlayersMessage = "";	//Winning players message for output

	pCurrentPlayer = mpPlayersList->GetHead();	//Get first player

	//Loop through players in list
	while (pCurrentPlayer)
	{
		//If player is one of the winning players then run
		if (pCurrentPlayer->GetBalance() == pHighestBalance)
		{
			winningPlayers.push_back(pCurrentPlayer->GetName());	//Add player to winningPlayers vector

			countWinningPlayers++;	//Increment count of winning players
		}

		pCurrentPlayer = pCurrentPlayer->GetNext();
	}

	vector<string>::iterator winningPlayersIterator = winningPlayers.begin();	//Iterator for winningPlayers vector

	//If multiple winning players, get names from winningPlayers vector
	//Else, get first name from winningPlayers vector
	if (countWinningPlayers > 1)
	{
		//Loop through winningPlayers vector
		while (winningPlayersIterator != winningPlayers.end())
		{
			//Add comma or and to output message depending
			//on where player name is in the list
			if ((*winningPlayersIterator) == winningPlayers.back())
			{
				winningPlayersMessage += " and ";
			}
			else if ((*winningPlayersIterator) != winningPlayers.front())
			{
				winningPlayersMessage += ", ";
			}

			//Add player name to output message
			winningPlayersMessage += (*winningPlayersIterator);

			++winningPlayersIterator;
		}

		winningPlayersMessage += " win!";	//Add ending to output message
	}
	else
	{
		//Create winning player message
		winningPlayersMessage += winningPlayers.front();
		winningPlayersMessage += " wins!";
	}

	cout << winningPlayersMessage << endl;	//Output winning players message
}