#pragma once
#include <random>

enum class COLORS { RED=0, BLUE, WHITE, GREEN, YELLOW, ORANGE };


class RubixCubeFace
{
	//Vector of vectors to store colors
	//Some way to store which face is adjacent to which?   No let the RubixCube itself handle that
	//IsSolved() fn
	
public:
	RubixCubeFace() : myFace(std::vector<std::vector<int>>(3, std::vector<int>(3, (int)COLORS::RED))) {}
	RubixCubeFace(COLORS c) : myFace(std::vector<std::vector<int>>(3, std::vector<int>(3, (int)c))) {}

	RubixCubeFace(const RubixCubeFace& other)
	{
		if (this != &other)
		{
			myFace = other.myFace;
		}
	}


	


	bool isSolved() const {

		int c = myFace[0][0];

		for (int i = 0; i < myFace.size(); i++)
		{
			for (int j = 0; j < myFace[i].size(); j++)
			{
				if(c!=myFace[i][j])
				{
					return false;
				}
			}
		}

		return true;
	}

	~RubixCubeFace() {}

	std::vector<std::vector<int>> myFace;

	//Returns A. the color that takes up the most spaces on this face and B. how many spaces it takes up
	std::pair<COLORS, int> biggestColor();
	
	//Returns the number of rows that are all a single color--they don't all have to be the same color!
	int numSolidRows();

	//Same as above, but for columns instead
	int numSolidCols();
};


class RubixCube
{
public:
	RubixCube()
	{
	//	faces = {  RubixCubeFace(COLORS::RED),  RubixCubeFace(COLORS::BLUE),  RubixCubeFace(COLORS::GREEN), RubixCubeFace(COLORS::ORANGE),  RubixCubeFace(COLORS::YELLOW),  RubixCubeFace(COLORS::WHITE) };
	
		faces[0] = RubixCubeFace(COLORS::RED);
		faces[1] = RubixCubeFace(COLORS::BLUE);
		faces[2] = RubixCubeFace(COLORS::YELLOW);
		faces[3] = RubixCubeFace(COLORS::GREEN);
		faces[4] = RubixCubeFace(COLORS::WHITE);
		faces[5] = RubixCubeFace(COLORS::ORANGE);


	
	}

	void Twist(int rowColumn, int index, int numTurns);  //Twist Rubix Cube.   
	// rowColumn >=0, turn rows,   rowColumn < 0 turn columns
	//index:  turn the 1st, 2nd, or 3rd row/column
	//Number of times to turn specified row/column



	//Note:  Don't need to worry about up vs. down  and  clockwise vs. counterclockwise turns:  three of one will always be equivalent to one of the other
	//Similar to how 3 left turns make a right turn
	
	
	//Helper methods for Twisting
	void TurnRow(int row);  //Turn row once
	void TurnColumn(int col);  //Turn column once




	~RubixCube() {};

	RubixCubeFace faces[6];

	//static std::vector<int> neighbors;


	//const static int[][] neighbors =	{1,3,4,5},{0,2,4,5},{1,3,4,5},{0,2,4,5},{0,1,2,3},{0,1,2,3};
	static const int neighbors[6][4];// = { 1,3,4,5 }, { 0,2,4,5 }, { 1,3,4,5 }, { 0,2,4,5 }, { 0,1,2,3 }, { 0,1,2,3 };



	//Vector of faces to store all 6 faces of cube--THEN the hard part will be rotating it properly
	//Number each face, keep track of which faces have which neighbors
	//Diagram will be very helpful

	/*  Faces 0-5

	Face : Neighbors
	      [4]
	       |
	[0] - [1] - [2] - [3] 
	       |
		  [5]


	0 : 1,2,4,5
	1 : 0,2,4,3
	2 : 1,3,4,5
	3 : 0,2,4,5
	4 : 0,1,2,3
	5 : 0,1,2,3
	
	
	
	
	*/

	//Is solved fn

	bool IsSolved() { return (faces[0].isSolved() && faces[1].isSolved() && faces[2].isSolved() && faces[3].isSolved() && faces[4].isSolved() && faces[5].isSolved()); }



	//Fitness functions

	//# of sides solved


	//Max sides solved:  6
	//Max rows & cols solved:  3 rows, 3 cols per face, 6 faces -- 3 x 6 = 18
	//Max squares filled:  9 squares per face, 6 faces -- 9 x 6 = 54

	int SidesSolved() { int count = 0; for (int i = 0; i < 6; i++) { if (faces[i].isSolved()) { count++; } }   return count; }
	
	//Returns number of rows that are a solid color
	int RowsFilled();
	//Same as above, but columns instead
	int ColsFilled();

	//For each color that dominates a particular face, it has some number of squares it takes up, more than any other color
	//This function returns the sum of these
	int SquaresFilled();


};

