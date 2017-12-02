#include "RubixCube.h"


										//Right, left, top, & bottom neighbors--in that order!
const int RubixCube::neighbors[6][4] = { { 1,3,4,5 }, { 2,0,4,5 }, { 3,1,4,5 }, { 0,2,4,5 }, { 2,0,3,1 }, { 2,0,1,3 } };





void RubixCube::TurnRow(int row)
{

	std::vector<int> temp[4];
	//Based on my drawing, the rows involved in HORIZONTAL MOVES are:  0,1,2,3
	for (int i = 0; i < 4; i++)
	{
		temp[i] = faces[(i+1)%4].myFace[row];
	}

	for (int i = 0; i < 4; i++)
	{
		faces[i].myFace[row] = temp[i];
	}

}


void RubixCube::TurnColumn(int col)
{
	std::vector<int> temp[4]{ std::vector<int>(3),std::vector<int>(3) ,std::vector<int>(3) ,std::vector<int>(3) };



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


	//4->1
	for (int i = 0; i < 3; i++)
	{
		faces[4].myFace[i][col] = temp[0][i];
	}
//3->4
	for (int i = 0; i < 3; i++)
	{
		faces[3].myFace[i][col] = temp[1][i];
	}
//5->3	
	for (int i = 0; i < 3; i++)
	{
		faces[5].myFace[i][col] = temp[2][i];
	}
//1->5
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


int RubixCube::RowsFilled()
{
	int out = faces[0].numSolidRows();

	for (int i = 1; i < 6; i++)
	{
		out += faces[i].numSolidRows();
	}
	return out;
}


int RubixCube::ColsFilled()
{

	int out = faces[0].numSolidCols();

	for (int i = 1; i < 6; i++)
	{
		out += faces[i].numSolidCols();
	}

	return out;
}


int RubixCube::SquaresFilled()
{
	int out = faces[0].biggestColor().second;

	for (int i = 1; i < 6; i++)
	{
		out += faces[i].biggestColor().second;
	}

	return out;
}



std::pair<COLORS, int> RubixCubeFace::biggestColor()
{
	std::pair<COLORS, int> pairs[6] = { std::pair<COLORS,int>(COLORS::RED, 0),  std::pair<COLORS,int>(COLORS::YELLOW, 0), std::pair<COLORS,int>(COLORS::ORANGE, 0), std::pair<COLORS,int>(COLORS::GREEN, 0), std::pair<COLORS,int>(COLORS::BLUE, 0), std::pair<COLORS,int>(COLORS::WHITE, 0) };

	for (int i = 0; i < myFace.size(); i++)
	{
		for (int j = 0; j < myFace[i].size(); j++)
		{
			for (int x = 0; x < 6; x++)
			{
				if (myFace[i][j] == (int)pairs[x].first)
				{
					pairs[x].second++;
				}
			}
		}
	}
	
	int maxIndex = 0;
	for (int i = 1; i < 6; i++)
	{
		if (pairs[maxIndex].second < pairs[i].second)
		{
			maxIndex = i;
		}
	}

	return pairs[maxIndex];

}



int RubixCubeFace::numSolidRows()
{
	int out = 0;

	for (int i = 0; i < myFace.size(); i++)
	{
		if (myFace[i][0] == myFace[i][1] && myFace[i][1] == myFace[i][2])  //Can probably write this more generically to scale size of Rubix Cube more easily but eh
		{
			out++;
		}
	}
	return out;
}

int RubixCubeFace::numSolidCols()
{
	int out = 0;

	for (int i = 0; i < myFace[0].size(); i++)
	{
		if (myFace[0][i] == myFace[1][i] && myFace[1][i] == myFace[2][i])  //Can probably write this more generically to scale size of Rubix Cube more easily but eh
		{
			out++;
		}
	}
	return out;
}