#pragma once
#ifndef miningProblem_h_
#define miningProblem_h_

#define length 8
#define width 8
//#define startingGas 500
#define startingGas 100
#define baseReward 1000
#define addedReward 1

//#define defaultProbAdjYgivenY 0.34782 //100
//#define defaultProbAdjYgivenN 0.11236 //100

//#define defaultProbAdjYgivenY 0.3333333333333 //500
//#define defaultProbAdjYgivenN 0.0837696335079 //500

#define defaultProbAdjYgivenY 0.46875 //1000
#define defaultProbAdjYgivenN 0.072916666666667 //1000


struct Position
{
	int x;
	int y;
	bool operator==(const Position& a) const
	{
		return (x == a.x && y == a.y);
	}
};

int manhDist(Position pos1, Position pos2);

#endif