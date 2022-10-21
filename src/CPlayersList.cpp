//Name: Alex Reed
//Student ID: G20690958

#include "CPlayersList.h"

//Constructor
CPlayersList::CPlayersList()
{
	mpHead = nullptr;	//Initialise pointer to first CPlayer in list
}

//Return pointer to first CPlayer in list
CPlayer* CPlayersList::GetHead()
{
	return mpHead.get();
}

//Return pointer to first solvent CPlayer in list
CPlayer* CPlayersList::GetFirstSolventPlayer()
{
	CPlayer* pPlayer = mpHead.get();	//Start with first player in list
	bool playerFound = false;

	//Loop through player list until solvent player found
	while (!playerFound && pPlayer)
	{
		//If player is solvent, change flag
		//Else, get next player
		if (pPlayer->GetSolvent())
		{
			playerFound = true;
		}
		else
		{
			pPlayer = pPlayer->GetNext();
		}
	}

	return pPlayer;
}

//Return pointer to next solvent CPlayer in list
CPlayer* CPlayersList::GetNextSolventPlayer(CPlayer* pCurrentPlayer)
{
	CPlayer* pNextPlayer = nullptr;	//Initialise pointer to next player

	//If there is a next player in the list then run
	if (pCurrentPlayer->GetNext())
	{
		pNextPlayer = pCurrentPlayer->GetNext();	//Set pointer to next player
		bool playerSolvent = pNextPlayer->GetSolvent();	//Check if next player is solvent

		//Loop until solvent player found or end of list reached
		while (!playerSolvent && pNextPlayer)
		{
			pNextPlayer = pNextPlayer->GetNext();	//Set pointer to next player
			
			if (pNextPlayer)
			{
				playerSolvent = pNextPlayer->GetSolvent();	//Check if next player is solvent
			}
		}
	}

	return pNextPlayer;
}

//Return number of solvent players in list
int CPlayersList::CountSolventPlayers()
{
	CPlayer* pCurrent = mpHead.get();	//Start with first player in list
	int count = 0;	//Initialise counter

	//Loop through player list
	while (pCurrent)
	{
		//If player is solvent, increment counter
		if (pCurrent->GetSolvent())
		{
			count++;
		}

		pCurrent = pCurrent->GetNext();
	}

	return count;
}

//Create new CPlayer and add to list
void CPlayersList::NewPlayer(string name, CGameManager* pGame)
{
	auto pNewPlayer{ make_unique<CPlayer>(name, pGame) };	//Create new pointer to CPlayer

	PushBack(move(pNewPlayer));	//Move new pointer to back of list
}

//Push input pointer to CPlayer to back of list
void CPlayersList::PushBack(unique_ptr <CPlayer> pNewPlayer)
{
	CPlayer* pCurrent = mpHead.get();	//Start with first player in list

	//If players already in list then go through list
	//and add new player to end. Else, set new player
	//as head of list.
	if (pCurrent)
	{
		while (pCurrent->GetNext())
		{
			pCurrent = pCurrent->GetNext();
		}

		pCurrent->SetNext(move(pNewPlayer));
	}
	else
	{
		mpHead = move(pNewPlayer);
	}
}