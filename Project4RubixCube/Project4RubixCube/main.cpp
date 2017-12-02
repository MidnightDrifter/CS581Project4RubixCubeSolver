#include "RubixCube.h"
#include <random>
#include <iostream>
#include <chrono>
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
const int ONE_SEC = 1;
const int TEN_SEC = 10;
const int THIRTY_SEC = 30;
const int ONE_MIN = 60;
const int FIVE_MIN = 60 * 5;



void ScrambleCube(RubixCube* c)
{
	for (int i = 0; i < STARTING_TURNS; i++)
	{
		c->Twist(rand() % 2, rand() % 3, rand() % 3 + 1);
	}

}

int main()
{
	std::chrono::seconds elapsedTime(0);
	std::chrono::seconds maxTime(ONE_SEC);


	std::vector<RubixCube>permutations(150);

	RubixCube startState;

	RubixCube* startingCube = new RubixCube();

	ScrambleCube(startingCube);

	unsigned numIterations = 0, numRandomRestarts=0, localMinima=100;
	
	RubixCube* testCube = new RubixCube();

	
	
	while(elapsedTime < std::chrono::seconds(ONE_SEC))   //(numIterations <MAX_ITERATIONS)  // or for some number of iterations
	{
	
		
		auto start = std::chrono::system_clock::now();
		
		numIterations++;




	if(startingCube->IsSolved())
	{
		std::cout << "Rubix Cube SOLVED!  It took:  " << elapsedTime.count() << " seconds after an initial " << STARTING_TURNS << "." << std::endl;
		return 1;
		//break;
	}


	else
	{//
		*testCube = *startingCube;
		//Neighbor relationships:   rotate rows with some number of turns, rotate cols with some number fo turns, rotate BOTH with some number of turns
		
	//	int index = rand() % 3;



		for (int i = 0; i < 6; i++)  //For each face on the cube
		{
			for (int j = 0; j < 3; j++)  //For each row, column, row & column
			{
				for (int k = 1; k <= 3; k++)  //For 1-3 turns
				{
					RubixCube temp[3] = { RubixCube(*startingCube), RubixCube(*startingCube), RubixCube(*startingCube) };
					temp[0].TurnRow(j, k);
					
					temp[1].TurnColumn(j, k);

					temp[2].TurnColumn(j, k);
					temp[2].TurnRow(j, k);

					permutations.push_back(temp[0]);
					permutations.push_back(temp[1]);
					permutations.push_back(temp[2]);
				}
			
			}
		}



		//Rotate rows
/*
		for (int i = 0; i < NUM_ROTATIONS_ROWS; i++)
		{
			testCube->TurnRow(index);
		}

		//Rotate cols
		for (int i = 0; i < NUM_ROTATIONS_COLS; i++)
		{
			testCube->TurnColumn(index);
		}
		*/
		//Rotate rows & cols
	//	for (int i = 0; i < NUM_ROTATIONS_BOTH; i++)
		//{
		//	testCube->TurnColumn(index);
		//	testCube->TurnRow(index);
		
		//}

		


		//Fitness fns
		
		//Sides solved
		//if(testCube->SidesSolved() > startingCube->SidesSolved())
		
		//# rows & cols solved
		//if((testCube->RowsFilled() + testCube->ColsFilled()) > (startingCube->ColsFilled() + startingCube->RowsFilled()))
		
		//# squares solved
		//if (testCube->SquaresFilled() > startingCube->SquaresFilled())
		//	{
		//	*startingCube = *testCube;
		//	}


		int index = -1;
		int min = startingCube->SquaresFilled();
		for (int i = 0; i<= permutations.size(); i++)
		{
			if (min > permutations[i].SquaresFilled())
			{
				index = i;
				min = permutations[i].SquaresFilled();
			}
		}

		if (index == -1)
		{
			//Increment random reset counter, random reset!

			numRandomRestarts++;
			*startingCube = startState;
			ScrambleCube(startingCube);
		}

	
	}

	auto end = std::chrono::system_clock::now();


	elapsedTime += std::chrono::duration_cast<std::chrono::seconds>(end - start);


	}
	
	
	std::cout << "Rubix cube unsolved after:  " << elapsedTime.count() << " seconds with an initial " << STARTING_TURNS <<" turns." << std::endl;
	return 0;
	
	



}