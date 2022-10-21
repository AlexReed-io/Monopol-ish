//Name: Alex Reed
//Student ID: G20690958

#include "CPlayer.h"
#include "CGameManager.h"
#include "CBank.h"
#include "CSquare.h"
#include "CProperty.h"
#include "CStation.h"

//Constructor
CPlayer::CPlayer(string name, CGameManager* pGame)
{
	mName = name;	//Initialise name to input name
	mBalance = 0;	//Initialise balance
	mpPosition = nullptr;	//Initialise pointer to position
	mSolvent = true;	//Initialise solvent flag
	mpNext = nullptr;	//Initialise pointer to next player
	mpBank = pGame->GetBankPtr();	//Get pointer to CBank class

	IncreaseBalance(1500);	//Set starting balance
}

//Return player's name
string CPlayer::GetName()
{
	return mName;
}

//Return player's current balance
int CPlayer::GetBalance()
{
	return mBalance;
}

//Return pointer to player's position
CSquare* CPlayer::GetPosition()
{
	return mpPosition;
}

//Return flag for if player is solvent
bool CPlayer::GetSolvent()
{
	return mSolvent;
}

//Return pointer to next CPlayer in list
CPlayer* CPlayer::GetNext()
{
	return mpNext.get();
}

//Return pointer to cheapest owned property
CProperty* CPlayer::GetCheapestProperty()
{
	ownedPropertiesIter ownedPropertiesIterator = mOwnedProperties.begin();	//Iterator for mOwnedProperties vector
	CProperty* pProperty = nullptr;	//Pointer to cheapest property
	bool propertyFound = false;

	//Loop through properties in vector unless property found
	while (ownedPropertiesIterator != mOwnedProperties.end() && !propertyFound)
	{
		//If property is not mortgaged then run
		if ((*ownedPropertiesIterator)->GetMortgaged() == false)
		{
			pProperty = *ownedPropertiesIterator;	//Set property pointer to property from vector
			propertyFound = true;	//Set found flag to true
		}

		++ownedPropertiesIterator;	//Increment iterator
	}

	return pProperty;
}

//Return pointer to cheapest mortgaged property
CProperty* CPlayer::GetCheapestMortgagedProperty()
{
	ownedPropertiesIter ownedPropertiesIterator = mOwnedProperties.begin();	//Iterator for mOwnedProperties vector
	CProperty* pProperty = nullptr;	//Pointer to cheapest mortgaged property
	bool propertyFound = false;

	//Loop through properties in vector unless property found
	while (ownedPropertiesIterator != mOwnedProperties.end() && !propertyFound)
	{
		//If property is mortgaged then run
		if ((*ownedPropertiesIterator)->GetMortgaged() == true)
		{
			pProperty = *ownedPropertiesIterator;	//Set property pointer to property from vector
			propertyFound = true;	//Set found flag to true
		}

		++ownedPropertiesIterator;	//Increment iterator
	}

	return pProperty;
}

//Output player's current balance
void CPlayer::DisplayBalance()
{
	//If player is solvent or not, display relevant message
	if (mSolvent)
	{
		cout << mName << " has " << POUND << mBalance << endl;
	}
	else
	{
		cout << mName << " is bankrupt" << endl;
	}
}

//Increase player's balance and decrease bank balance by input amount
void CPlayer::IncreaseBalance(int amount)
{
	mBalance += amount;	//Add input amount to player's balance
	mpBank->DecreaseBalance(amount);	//Decrease bank balance by input amount

	CProperty* pCheapestMortgagedProperty = GetCheapestMortgagedProperty();	//Get pointer to cheapest mortgaged property

	//While player's balance is greater than cost of cheapest mortgaged property
	//then buy back cheapest mortgaged property
	while (pCheapestMortgagedProperty && pCheapestMortgagedProperty->GetCost() < mBalance)
	{
		BuyBackCheapestMortgaged();

		pCheapestMortgagedProperty = GetCheapestMortgagedProperty();
	}
}

//Decrease player's balance and increase bank balance by input amount
void CPlayer::DecreaseBalance(int amount)
{
	mBalance -= amount;	//Subtract input amount from player's balance
	mpBank->IncreaseBalance(amount);	//Increase bank balance by input amount

	//If balance is less than zero then try to
	//mortgage properties. Else, add input
	//amount to bank balance
	if (mBalance < 0)
	{
		CProperty* pCheapestProperty = GetCheapestProperty();	//Get pointer to cheapest owned property
		
		//While balance is less than zero and player has
		//owned (non mortgaged) properties then mortgage
		//cheapest property
		while (mBalance < 0 && pCheapestProperty)
		{
			MortgageCheapestProperty();

			pCheapestProperty = GetCheapestProperty();
		}

		//If balance is still less than zero then
		//set solvent flag to false
		if (mBalance < 0)
		{
			cout << mName << " is bankrupt and loses the game" << endl;	//Output message
			
			int overpaid = -mBalance;	//Set overpaid amount to balance left below zero
			mpBank->DecreaseBalance(overpaid);	//Decrease bank balance by overpaid amount
			mSolvent = false;

			ownedPropertiesIter ownedPropertiesIterator = mOwnedProperties.begin();	//Iterator for mOwnedProperties vector

			//Loop through mOwnedProperties vector to remove
			//player as owner
			while (ownedPropertiesIterator != mOwnedProperties.end())
			{
				(*ownedPropertiesIterator)->SetOwner(nullptr);	//Set property owner to null
				(*ownedPropertiesIterator)->SetMortgaged(false);	//Revert property's mortgaged flag

				++ownedPropertiesIterator;	//Increment iterator
			}

			ownedStationsIter ownedStationsIterator = mOwnedStations.begin();	//Iterator for mOwnedStations vector

			//Loop through mOwnedStations vector
			//to remove player as owner
			while (ownedStationsIterator != mOwnedStations.end())
			{
				(*ownedStationsIterator)->SetOwner(nullptr);	//Set property owner to null

				++ownedStationsIterator;	//Increment iterator
			}
		}
	}
}

//Increase player's balance by input amount
void CPlayer::ReceiveRent(int amount)
{
	mBalance += amount;	//Add input amount to player's balance

	CProperty* pCheapestMortgagedProperty = GetCheapestMortgagedProperty();	//Get pointer to cheapest mortgaged property

	//While player's balance is greater than cost of cheapest mortgaged property
	//then buy back cheapest mortgaged property
	while (pCheapestMortgagedProperty && pCheapestMortgagedProperty->GetCost() < mBalance)
	{
		BuyBackCheapestMortgaged();

		pCheapestMortgagedProperty = GetCheapestMortgagedProperty();
	}
}

//Pay input amount to input CPlayer
void CPlayer::PayRent(int amount, CPlayer* pOwner)
{
	mBalance -= amount;	//Subtract input amount from player's balance
	int owedToOwner = amount;	//Set amount owed to owner as input amount

	//If balance is less than zero then try to mortgage properties
	if (mBalance < 0)
	{
		CProperty* pCheapestProperty = GetCheapestProperty();	//Get pointer to cheapest owned property

		//While balance is less than zero and player has
		//owned (non mortgaged) properties then mortgage
		//cheapest property
		while (mBalance < 0 && pCheapestProperty)
		{
			MortgageCheapestProperty();

			pCheapestProperty = GetCheapestProperty();
		}

		//If balance is still less than zero then
		//set solvent flag to false
		if (mBalance < 0)
		{
			cout << mName << " is bankrupt and loses the game" << endl;	//Output message
			
			owedToOwner += mBalance;	//Add negative balance to amount owed to owner
			mSolvent = false;

			ownedPropertiesIter ownedPropertiesIterator = mOwnedProperties.begin();	//Iterator for mOwnedProperties vector

			//Loop through mOwnedProperties vector
			//to remove player as owner
			while (ownedPropertiesIterator != mOwnedProperties.end())
			{
				(*ownedPropertiesIterator)->SetOwner(nullptr);	//Set property owner to null
				(*ownedPropertiesIterator)->SetMortgaged(false);	//Revert property's mortgaged flag

				++ownedPropertiesIterator;	//Increment iterator
			}

			ownedStationsIter ownedStationsIterator = mOwnedStations.begin();	//Iterator for mOwnedStations vector

			//Loop through mOwnedStations vector
			//to remove player as owner
			while (ownedStationsIterator != mOwnedStations.end())
			{
				(*ownedStationsIterator)->SetOwner(nullptr);	//Set property owner to null

				++ownedStationsIterator;	//Increment iterator
			}
		}
	}

	pOwner->ReceiveRent(owedToOwner);	//Pay owed amount to owner
}

//Set player's position to input pointer
void CPlayer::SetPosition(CSquare* pSquare)
{
	mpPosition = pSquare;
}

//Buy input property
void CPlayer::BuyProperty(CProperty* pBoughtProperty)
{
	int boughtPropertyCost = pBoughtProperty->GetCost();	//Get cost for bought property
	int boughtPropertyGroup = pBoughtProperty->GetGroup();	//Get group for bought property
	string boughtPropertyColour = pBoughtProperty->GetColour();	//Get colour for bought property
	
	mOwnedProperties.push_back(pBoughtProperty);	//Add pointer to bought property to mOwnedProperties vector
	SortOwnedPropertiesByCost();	//Sort mOwnedProperties vector by property cost in ascending value
	pBoughtProperty->SetOwner(this);	//Set bought property owner to a pointer to this player
	DecreaseBalance(boughtPropertyCost);	//Decrease player's balance and increase bank balance by bought property cost

	int propertiesOwnedInGroup = 0;	//Count number of owned properties in bought property's group

	ownedPropertiesIter ownedPropertiesIterator = mOwnedProperties.begin();	//Iterator for mOwnedProperties vector

	//Loop through mOwnedProperties vector
	while (ownedPropertiesIterator != mOwnedProperties.end())
	{
		//If property in vector is in same group as bought property
		//then increment count variable
		if ((*ownedPropertiesIterator)->GetGroup() == boughtPropertyGroup)
		{
			propertiesOwnedInGroup++;
		}
		
		++ownedPropertiesIterator;	//Increment iterator
	}

	int totalPropertiesInGroup = pBoughtProperty->GetTotalPropertiesInGroup();	//Get total properties in group from bought property

	//If player owns all properties in group then run
	if (totalPropertiesInGroup == propertiesOwnedInGroup)
	{
		//Loop through properties in mOwnedProperties vector
		for (auto pProperty : mOwnedProperties)
		{
			//If property is in same group as bought property
			//then double the property's rent
			if (pProperty->GetGroup() == boughtPropertyGroup)
			{
				int currentRent = pProperty->GetRent();
				int doubledRent = currentRent * 2;
				
				pProperty->SetRent(doubledRent);
			}
		}

		cout << mName << " owns all " << boughtPropertyColour << " properties so the rent for these is doubled" << endl;	//Output message
	}
}

//Sort mOwnedProperties vector by property cost in ascending value
void CPlayer::SortOwnedPropertiesByCost()
{
	sort(mOwnedProperties.begin(), mOwnedProperties.end(), compareCosts);	//Sort vector using compareCosts function
}

//Mortgage cheapest property
void CPlayer::MortgageCheapestProperty()
{
	CProperty* pCheapestProperty = GetCheapestProperty();	//Get pointer to cheapest non-mortgaged owned property

	//If player has non-mortgaged owned property then run
	if (pCheapestProperty)
	{
		int propertyCost = pCheapestProperty->GetCost();	//Get cost of cheapest non-mortgaged owned property
		pCheapestProperty->SetMortgaged(true);	//Change property's mortgaged flag
		IncreaseBalance(propertyCost);	//Increase player's balance and decrease bank balance by property's cost

		cout << mName << " mortgages " << pCheapestProperty->GetName() << " for " << POUND << propertyCost << endl;	//Output message
	}
}

//Buy back cheapest mortgaged property
void CPlayer::BuyBackCheapestMortgaged()
{
	CProperty* pCheapestMortgagedProperty = GetCheapestMortgagedProperty();	//Get pointer to cheapest mortgaged property

	//If player has mortgaged property then run
	if (pCheapestMortgagedProperty)
	{
		int propertyCost = pCheapestMortgagedProperty->GetCost();	//Get cost of cheapest mortgaged owned property
		pCheapestMortgagedProperty->SetMortgaged(false);	//Change property's mortgaged flag
		DecreaseBalance(propertyCost);	//Decrease player's balance and increase bank balance by property's cost

		cout << mName << " buys back " << pCheapestMortgagedProperty->GetName() << " for " << POUND << propertyCost << endl;	//Output message
	}
}

//Buy input station
void CPlayer::BuyStation(CStation* pBoughtStation)
{
	DecreaseBalance(pBoughtStation->GetCost());	//Decrease player's balance and increase bank balance by station's cost
	mOwnedStations.push_back(pBoughtStation);	//Add pointer to bought station to mOwnedStations vector
	pBoughtStation->SetOwner(this);	//Set bought station owner to a pointer to this player
}

//Set mpNext to input pointer
void CPlayer::SetNext(unique_ptr <CPlayer> pNext)
{
	mpNext = move(pNext);
}

//Compare costs of input pointers
bool compareCosts(CProperty* pProperty1, CProperty* pProperty2)
{
	return (pProperty1->GetCost() < pProperty2->GetCost());
}