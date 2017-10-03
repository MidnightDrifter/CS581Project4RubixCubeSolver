#include "RubixCube.h"


										//Right, left, top, & bottom neighbors--in that order!
const int RubixCube::neighbors[6][4] = { { 1,3,4,5 }, { 2,0,4,5 }, { 3,1,4,5 }, { 0,2,4,5 }, { 2,0,3,1 }, { 2,0,1,3 } };





void RubixCube::TurnRow(int row)
{

	std::vector<int> temp[4];
	//Based on my drawing, the rows involved in HORIZONTAL MOVES are:  0,1,2,3
	for (int i = 0; i < 4; i++)
	{
		temp[i] = faces[i].myFace[row];
	}

	for (int i = 0; i < 4; i++)
	{
		faces[i].myFace[(row + 1) % 4] = temp[i];
	}

}


void RubixCube::TurnColumn(int col)
{
	std::vector<int> temp[4];
	//Based on my drawing, the rows involved in VERTICAL MOVES are:  1,4,3,5
	
	for (int i = 0; i < 3; i++)
	{
		temp[0][i] = faces[1].myFace[i][col];
	}

	for (int i = 0; i < 3; i++)
	{
		temp[1][i] = faces[4].myFace[i][col];
	}

	for (int i = 0; i < 3; i++)
	{
		temp[2][i] = faces[3].myFace[i][col];
	}

	for (int i = 0; i < 3; i++)
	{
		temp[3][i] = faces[5].myFace[i][col];
	}



	for (int i = 0; i < 3; i++)
	{
		faces[4].myFace[i][col] = temp[0][i];
	}

	for (int i = 0; i < 3; i++)
	{
		faces[3].myFace[i][col] = temp[1][i];
	}
	
	for (int i = 0; i < 3; i++)
	{
		faces[5].myFace[i][col] = temp[2][i];
	}

	for (int i = 0; i < 3; i++)
	{
		faces[1].myFace[i][col] = temp[3][i];
	}


}


void RubixCube::Twist(int rowCol, int index, int numTurns)
{
	if (rowCol >= 0)
	{
		for (int i = 0; i < numTurns; i++)
		{
			TurnRow(index);
		}
	}

	else
	{
		for (int i = 0; i < numTurns; i++)
		{
			TurnColumn(index);
		}
	}
}
