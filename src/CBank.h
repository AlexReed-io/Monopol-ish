//Name: Alex Reed
//Student ID: G20690958

#pragma once

#include <iostream>
using namespace std;

class CBank
{
protected:
	int mBalance;	//Current bank balance
public:
	CBank();	//Constructor

	int GetBalance();	//Return current bank balance
	void IncreaseBalance(int amount);	//Increase bank balance by input amount
	void DecreaseBalance(int amount);	//Decrease bank balance by input amount
};

