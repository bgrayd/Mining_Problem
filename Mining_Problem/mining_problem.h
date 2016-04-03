#pragma once
#ifndef miningProblem_h_
#define miningProblem_h_

#define length 5
#define width 5

#define defaultProbAdjYgivenY 0.1
#define defaultProbAdjYgivenN 0.05

struct Position
{
	int x;
	int y;
};

int manhDist(Position pos1, Position pos2);

#endif