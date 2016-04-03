#pragma once
#ifndef miningProblem_h_
#define miningProblem_h_

#define length 8
#define width 8
#define startingGas 500
#define baseReward 50
#define addedReward 20

#define defaultProbAdjYgivenY 0.1
#define defaultProbAdjYgivenN 0.05

struct Position
{
	int x;
	int y;
};

int manhDist(Position pos1, Position pos2);

#endif