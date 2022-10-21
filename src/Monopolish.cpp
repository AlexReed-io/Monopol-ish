//Name: Alex Reed
//Student ID: G20690958

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "CGameManager.h"
using namespace std;

const char POUND = char(156);	//Set global £ variable

int main()
{
	{
		auto newGame{ make_unique<CGameManager>() };	//Create new pointer to CGameManager

		//Create players
		newGame->NewPlayer("Hamster");
		newGame->NewPlayer("Pumpkin");
		newGame->NewPlayer("Dog");
		newGame->NewPlayer("Jaguar");

		newGame->PlayGame();	//Play the game
	}

	_CrtDumpMemoryLeaks();	//Check for memory leaks
}