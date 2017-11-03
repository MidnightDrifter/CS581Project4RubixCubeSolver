#include "RubixCube.h"
#include <random>
const int STARTING_TURNS = 5;   //How many times to turn & jumble the Rubix Cube

enum IndexToTurn { FIRST = 0, SECOND, LAST };

enum RowOrColumn { ROW = 0, COLUMN };

enum NumTurns { ONE = 0,TWO,THREE };

const int MAX_SIDES_SOLVED = 6;		//Max sides solved:  6
const int MAX_ROWS_COLS_SOLVED= 18;	//Max rows & cols solved:  3 rows, 3 cols per face, 6 faces -- 3 x 6 = 18
const int MAX_SQUARES_FILLED=54;	//Max squares filled:  9 squares per face, 6 faces -- 9 x 6 = 54
int main()
{

	RubixCube startingCube;

	for (int i = 0; i < STARTING_TURNS; i++)
	{
		startingCube.Twist(rand() % 2, rand() % 3, rand() % 3 + 1);
	}





	const int indexChoice = FIRST;
	const int rowColumnChoice = ROW;
	const int numTurnsChoice = ONE;

	/*
	
	while(true)   or for some number of iterations

	{




	}
	
	
	
	
	*/




}