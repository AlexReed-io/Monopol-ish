//Name: Alex Reed
//Student ID: G20690958

#include "CDie.h"
#include "CPlayer.h"

//Constructor
CDie::CDie()
{
	mSeed = 1;	//Initialise seed value
	
	//Read in seed.txt file
	ifstream file("seed.txt");

	//If file can be opened, then run
	if (file.is_open())
	{
		file >> mSeed;	//Assign integer from file to mSeed variable
	}
	else
	{
		cout << "Couldn't open 'seed.txt' file so using 1 as seed" << endl << endl;
	}

	srand(mSeed);	//Set seed for random function to mSeed value
}

//Return next die roll number for input player
int CDie::Roll(CPlayer* pPlayer)
{
	int dieRoll = static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * 6.0f + 1);	//Create next die roll number

	cout << pPlayer->GetName() << " rolls " << dieRoll << endl;	//Output player die roll message
	
	return dieRoll;
}