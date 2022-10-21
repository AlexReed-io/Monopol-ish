//Name: Alex Reed
//Student ID: G20690958

#include "CBoard.h"

//Constructor
CBoard::CBoard()
{
	mSquaresCreated = false;	//Initialise flag to show if squares created
	mpHead = nullptr;	//Initialise pointer to first CSquare in list
	mpJailSquare = nullptr;	//Initialise pointer to Jail square

	CreateSquares();	//Read in text file to create squares
}

//Return flag for if squares created
bool CBoard::GetSquaresCreated()
{
	return mSquaresCreated;
}

//Return pointer to first CSquare in list
CSquare* CBoard::GetHead()
{
	return mpHead.get();
}

//Return pointer to next CSquare in list, looping back to start
CSquare* CBoard::GetNextSquare(CSquare* pCurrentSquare)
{
	CSquare* pNextSquare = nullptr;

	//If there is a next square then get pointer for it
	//If not, get pointer for first square in list
	if (pCurrentSquare->GetNext())
	{
		pNextSquare = pCurrentSquare->GetNext();
	}
	else
	{
		pNextSquare = mpHead.get();
	}

	return pNextSquare;
}

//Return pointer to Jail square
CSquare* CBoard::GetJailSquare()
{
	return mpJailSquare;
}

//Push input pointer to CSquare to back of list
void CBoard::PushBack(unique_ptr <CSquare> pNewSquare)
{
	AddColourGroup(pNewSquare.get());	//Add new CSquare group to mColourGroups vector
	
	CSquare* pCurrent = mpHead.get();
	
	//If jail square pointer hasn't been added, try to get it
	if (mpJailSquare == nullptr)
	{
		mpJailSquare = pNewSquare->GetJailSquare();
	}
	
	//Go through squares in list and add new square to back
	if (pCurrent)
	{
		while (pCurrent->GetNext())
		{
			pCurrent = pCurrent->GetNext();
		}

		pCurrent->SetNext(move(pNewSquare));	//Move new square to back of list
	}
	else
	{
		mpHead = move(pNewSquare);	//Move new square to head of list
	}
}

//Add input CSquare group to mColourGroups vector
void CBoard::AddColourGroup(CSquare* pNewSquare)
{
	int newSquareGroup = pNewSquare->GetGroup();

	//If new square is a property then run
	if (newSquareGroup != 10)
	{
		colourGroupsIter colourGroupsIterator = mColourGroups.begin();	//Iterator for mColourGroups vector
		bool foundGroup = false;

		//Loop through mColourGroups vector unless group found
		while (colourGroupsIterator != mColourGroups.end() && !foundGroup)
		{
			//If group found, increment total and set found flag to true
			if ((*colourGroupsIterator).mGroup == newSquareGroup)
			{
				(*colourGroupsIterator).mTotalSquares += 1;
				foundGroup = true;
			}

			++colourGroupsIterator;
		}

		//If group not found, add new group to back of vector
		if (!foundGroup)
		{
			mColourGroups.push_back({ newSquareGroup, 1 });
		}
	}
}

//Add total squares in colour group from mColourGroups vector to each property
void CBoard::AddGroupTotalsToProperties()
{
	CSquare* pCurrent = mpHead.get();

	//Loop through squares in list
	while (pCurrent)
	{
		//If square is a property then run
		if (pCurrent->GetGroup() != 10)
		{
			colourGroupsIter colourGroupsIterator = mColourGroups.begin();	//Iterator for mColourGroups vector
			bool groupFound = false;

			//Loop through mColourGroups vector unless group found
			while (colourGroupsIterator != mColourGroups.end() && !groupFound)
			{
				//If group found, set property's mTotalPropertiesInGroup variable to total squares
				//from mColourGroups vector
				if ((*colourGroupsIterator).mGroup == pCurrent->GetGroup())
				{
					pCurrent->SetTotalPropertiesInGroup((*colourGroupsIterator).mTotalSquares);
					groupFound = true;
				}

				++colourGroupsIterator;
			}
		}

		pCurrent = pCurrent->GetNext();
	}
}

//Read in text file to create squares
void CBoard::CreateSquares()
{
	ifstream file("monopolish.txt");

	//If file can be opened, then run
	if (file.is_open())
	{
		//Loop through each line of file
		while (file)
		{
			int type = 0;
			file >> type;	//Read in first integer of line to type variable

			//If type is suitable then run
			if (type != 0)
			{
				//Create new CSquare from type using ESquareType enum class
				//Move pointer to new CSquare to back of list of squares
				PushBack(move(NewSquare(ESquareType(type), file, mpJailSquare)));
			}
		}

		AddGroupTotalsToProperties();	//Add total squares in colour group from mColourGroups vector to each property
		mSquaresCreated = true;	//Set squares created flag to true
	}
	else
	{
		cout << "Couldn't open 'monopolish.txt' file" << endl;
	}
}