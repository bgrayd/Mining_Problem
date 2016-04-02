#pragma once

#define length 5
#define width 5

#define defaultProbAdjYgivenY 0.1
#define defaultProbAdjYgivenN 0.05

float probAdjYgivenY = defaultProbAdjYgivenY;
float probAdjYgivenN = defaultProbAdjYgivenN;

struct Position
{
	int x;
	int y;
};