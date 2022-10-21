//Name: Alex Reed
//Student ID: G20690958

#include "CBank.h"

//Constructor
CBank::CBank()
{
	mBalance = 20000;	//Initialise starting bank balance
}

int CBank::GetBalance()
{
	return mBalance;
}

//Increase bank balance by input amount
void CBank::IncreaseBalance(int amount)
{
	mBalance += amount;	//Add input amount to bank balance
}

//Decrease bank balance by input amount
void CBank::DecreaseBalance(int amount)
{
	//If decreased bank balance would still be positive then decrease bank balance
	if ((mBalance - amount) < 0)
	{
		cout << "Bank does not have sufficient funds" << endl;
	}
	else
	{
		mBalance -= amount;	//Subtract input amount from bank balance
	}
}