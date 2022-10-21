//Name: Alex Reed
//Student ID: G20690958

#include "CProperty.h"
#include "CGameManager.h"
#include "CBank.h"
#include "CPlayer.h"

//Constructor
CProperty::CProperty(istream& file) : CSquare(file)
{
	mCost = 0;	//Initialise property cost
	mRent = 0;	//Initialise property rent
	mGroup = 0;	//Initialise property group
	mColour = "";	//Initialise property colour
	mTotalPropertiesInGroup = 0;	//Initialise total number of properties in group
	mMortgaged = false;	//Initialise flag for if mortgaged
	mpOwner = nullptr;	//Initialise pointer to CPlayer owner of property

	file >> *this;	//Read data from file into mCost, mRent, and mGroup variables

	//Use property group and set property colour accordingly
	switch (mGroup)
	{
	case 0:
	{
		mColour = "red";
		break;
	}
	case 1:
	{
		mColour = "grey";
		break;
	}
	case 2:
	{
		mColour = "brown";
		break;
	}
	case 3:
	{
		mColour = "orange";
		break;
	}
	case 4:
	{
		mColour = "yellow";
		break;
	}
	case 5:
	{
		mColour = "green";
		break;
	}
	case 6:
	{
		mColour = "blue";
		break;
	}
	case 7:
	{
		mColour = "purple";
		break;
	}
	default:
	{

	}
	}
}

//Return property cost
int CProperty::GetCost()
{
	return mCost;
}

//Return property rent
int CProperty::GetRent()
{
	return mRent;
}

//Return property group
int CProperty::GetGroup()
{
	return mGroup;
}

//Return property colour
string CProperty::GetColour()
{
	return mColour;
}

//Return total number of properties in group
int CProperty::GetTotalPropertiesInGroup()
{
	return mTotalPropertiesInGroup;
}

//Return flag for if mortgaged
bool CProperty::GetMortgaged()
{
	return mMortgaged;
}

//Return pointer to CPlayer owner of property
CPlayer* CProperty::GetOwner()
{
	return mpOwner;
}

//Set mRent to input amount
void CProperty::SetRent(int rent)
{
	mRent = rent;
}

//Set mTotalPropertiesInGroup to input amount
void CProperty::SetTotalPropertiesInGroup(int total)
{
	mTotalPropertiesInGroup = total;
}

//Set mMortgaged to input bool
void CProperty::SetMortgaged(bool mortgaged)
{
	mMortgaged = mortgaged;
}

//Set mpOwner to input CPlayer pointer
void CProperty::SetOwner(CPlayer* pPlayer)
{
	mpOwner = pPlayer;
}

//Player lands on square
void CProperty::LandOn(CGameManager* pGame, CPlayer* pPlayer)
{
	cout << pPlayer->GetName() << " lands on " << mName << endl;	//Output lands on message

	CBank* pBank = pGame->GetBankPtr();	//Get pointer to CBank class
	
	//If property is not owned, player buys property
	//Else, if player is not owner then player pays rent to owner
	if (mpOwner == nullptr)
	{
		cout << pPlayer->GetName() << " buys " << mName << " for " << POUND << mCost << endl;	//Output message

		pPlayer->BuyProperty(this);	//Player buys property
	}
	else if (mpOwner != pPlayer)
	{
		//If property is not mortgaged then rent paid
		if (!mMortgaged)
		{
			cout << pPlayer->GetName() << " pays " << mpOwner->GetName() << " " << POUND << mRent << " rent" << endl;	//Output message
			
			pPlayer->PayRent(mRent, mpOwner);	//Pay rent amount from player to owner
		}
	}
}

//Player passes square
void CProperty::Pass(CGameManager* pGame, CPlayer* pPlayer)
{

}

//Set >> to read in cost, rent, and group from file
istream& operator >> (istream& inputStream, CProperty& property)
{
	inputStream >> property.mCost >> property.mRent >> property.mGroup;
	return inputStream;
}