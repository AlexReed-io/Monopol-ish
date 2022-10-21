//Name: Alex Reed
//Student ID: G20690958

#include "CSquare.h"

//Constructor
CSquare::CSquare(istream& file)
{
	mName = "";	//Initialise square name
	mpNext = nullptr;	//Initialise pointer to next CSquare in list
	mpJailSquare = nullptr;	//Initialise pointer to Jail square
	
	file >> *this;	//Read name from file into mName variable
}

//Virtual destructor
CSquare::~CSquare()
{

}

//Return square name
string CSquare::GetName()
{
	return mName;
}

//Return square cost
int CSquare::GetCost()
{
	return 0;
}

//Return square group
int CSquare::GetGroup()
{
	return 10;
}

//Return pointer to next CSquare in list
CSquare* CSquare::GetNext()
{
	return mpNext.get();
}

//Return pointer to Jail square
CSquare* CSquare::GetJailSquare()
{
	return mpJailSquare;
}

//Set mTotalPropertiesInGroup to input amount
void CSquare::SetTotalPropertiesInGroup(int total)
{

}

//Move input pointer to mpNext
void CSquare::SetNext(unique_ptr <CSquare> pNext)
{
	mpNext = move(pNext);
}

//Set >> to read in name from file
istream& operator>>(istream& inputStream, CSquare& square)
{
	bool anotherWord = false;	//Flag for if another word found
	int nextChar = 0;	//Next character in string as integer

	do
	{
		string word;	//Holds string from input

		inputStream >> word;	//Move first word from input to variable
		square.mName += word;	//Adds word to square name

		inputStream >> ws;	//Skip space between words

		nextChar = inputStream.peek();	//View next character in input

		//If next character is not a number and not at
		//end of file then set anotherWord flag to true
		anotherWord = !isdigit(nextChar) && nextChar != EOF;

		if (anotherWord) square.mName += " ";	//If another word then add space

	} while (anotherWord);	//Loop while there is another word
	
	return inputStream;
}