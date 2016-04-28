#pragma once
#ifndef miningProblem_h_
#define miningProblem_h_

#define length 8
#define width 8
#define startingGas 200
#define baseReward 1000
#define addedReward 1

//#define defaultProbAdjYgivenY 0.34782 //100
//#define defaultProbAdjYgivenN 0.11236 //100

#define defaultProbAdjYgivenY 0.3333333333333 //500
#define defaultProbAdjYgivenN 0.0837696335079 //500


struct Position
{
	int x;
	int y;
};

int manhDist(Position pos1, Position pos2);

#endif