#include "RubixCube.h"
#include <random>
#include <iostream>
const int STARTING_TURNS = 15;   //How many times to turn & jumble the Rubix Cube

enum IndexToTurn { FIRST = 0, SECOND, LAST };

enum RowOrColumn { ROW = 0, COLUMN };

enum NumTurns { ONE = 0,TWO,THREE };

const int MAX_SIDES_SOLVED = 6;		//Max sides solved:  6
const int MAX_ROWS_COLS_SOLVED= 18;	//Max rows & cols solved:  3 rows, 3 cols per face, 6 faces -- 3 x 6 = 18
const int MAX_SQUARES_FILLED=54;	//Max squares filled:  9 squares per face, 6 faces -- 9 x 6 = 54
const unsigned MAX_ITERATIONS = 100000;
const int NUM_ROTATIONS_ROWS = 1;
const int NUM_ROTATIONS_COLS = 1;
const int NUM_ROTATIONS_BOTH = 1;
int main()
{

	RubixCube* startingCube = new RubixCube();

	for (int i = 0; i < STARTING_TURNS; i++)
	{
		startingCube->Twist(rand() % 2, rand() % 3, rand() % 3 + 1);
	}

	unsigned numIterations = 0;

	RubixCube* testCube = new RubixCube();

	
	
	while(numIterations <MAX_ITERATIONS)  // or for some number of iterations
	{
	numIterations++;

	if(startingCube->IsSolved())
	{
		std::cout << "Rubix Cube SOLVED!  It took:  " << numIterations << " iterations after an initial " << STARTING_TURNS << "." << std::endl;
		return 1;
		//break;
	}


	else
	{
		*testCube = *startingCube;
		//Neighbor relationships:   rotate rows with some number of turns, rotate cols with some number fo turns, rotate BOTH with some number of turns
		
		int index = rand() % 3;


		//Rotate rows

		for (int i = 0; i < NUM_ROTATIONS_ROWS; i++)
		{
			testCube->TurnRow(index);
		}
/*
		//Rotate cols
		for (int i = 0; i < NUM_ROTATIONS_COLS; i++)
		{
			testCube->TurnColumn(index);
		}

		//Rotate rows & cols
		for (int i = 0; i < NUM_ROTATIONS_BOTH; i++)
		{
			testCube->TurnColumn(index);
			testCube->TurnRow(index);
		
		}

		*/


		//Fitness fns
		
		//Sides solved
		if(testCube->SidesSolved() > startingCube->SidesSolved())
		
		//# rows & cols solved
		//if((testCube->RowsFilled() + testCube->ColsFilled()) > (startingCube->ColsFilled() + startingCube->RowsFilled()))
		
		//# squares solved
		//if (testCube->SquaresFilled() > startingCube->SquaresFilled())
			{
			*startingCube = *testCube;
			}

	
	}




	}
	
	
	std::cout << "Rubix cube unsolved after:  " << numIterations << " iterations with an initial " << STARTING_TURNS <<" turns." << std::endl;
	return 0;
	




}