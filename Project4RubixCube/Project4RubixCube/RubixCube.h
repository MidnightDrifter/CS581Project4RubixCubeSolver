#pragma once
#include <random>

enum class COLORS { RED, BLUE, WHITE, GREEN, YELLOW, ORANGE };


class RubixCubeFace
{
	//Vector of vectors to store colors
	//Some way to store which face is adjacent to which?   No let the RubixCube itself handle that
	//IsSolved() fn
	
public:
	RubixCubeFace() : myFace(std::vector<std::vector<COLORS>>(3, std::vector<COLORS>(3, COLORS::RED))) {}
	RubixCubeFace(COLORS c) : myFace(std::vector<std::vector<COLORS>>(3, std::vector<COLORS>(3, c))) {}

	bool isSolved() const {

		COLORS c = myFace[0][0];

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

	std::vector<std::vector<COLORS>> myFace;
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
	~RubixCube();

	RubixCubeFace faces[6];

	//Vector of faces to store all 6 faces of cube--THEN the hard part will be rotating it properly
	//Number each face, keep track of which faces have which neighbors
	//Diagram will be very helpful

};

