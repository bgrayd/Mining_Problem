#include <stdlib.h>     /* abs */
#include "mining_problem.h"




/********************************************
*returns the manhattan distance between two points
*********************************************/
int manhattanDist(int x1, int y1, int x2, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}

/********************************************
*returns the manhattan distance between two points
*********************************************/
int manhattanDist(Position pos1, Position pos2)
{
	manhattanDist(pos1.x, pos1.y, pos2.x, pos2.y);
}

/*******************************************
*calcPOfD calculates the P(d_i)
*@param pOfDGivenT: where each cell k holds the value P(d_i | T_k), of size [length][width]
*@param pOfT: where each cell k holds P(T_k), of size [length][width]
*@return: the value P(d_i)
*******************************************/
float calcPOfD(float (*pOfDGivenT)[length][width], float (*pOfT)[length][width])
{
	float runningPOfD = 0;
	
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			if (((*pOfT)[i][j] != 1.0) && ((*pOfT)[i][j] != 0.0))
				runningPOfD = (*pOfDGivenT)[i][j] * (*pOfT)[i][j];
	
	return runningPOfD;
};

/*******************************************
*calcPOfD calculates the P(T_j)^1 = P(T_j | d_i), does the calculation in place
*@param pOfDGivenT: where each cell k holds the value P(d_i | T_k), of size [length][width]
*@param pOfT: where each cell k holds P(T_k), of size [length][width]
*@param pOfD: P(d)
*******************************************/
void calcPOfT(float(*pOfDGivenT)[length][width], float(*pOfT)[length][width], float pOfD)
{
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			if (((*pOfT)[i][j] != 1.0) && ((*pOfT)[i][j] != 0.0))
				(*pOfT)[i][j] = ((*pOfDGivenT)[i][j] * (*pOfT)[i][j]) / pOfD;
}

/*******************************************
*calcPOfD calculates the P(T_j)^1 = P(T_j | d_i), does the calculation in place
*@param pOfDGivenT: where each cell k holds the value P(d_i | T_k), of size [length][width]
*@param pOfT: where each cell k holds P(T_k), of size [length][width]
*******************************************/
void calcPOfT(float(*pOfDGivenT)[length][width], float(*pOfT)[length][width])
{
	float pOfD = calcPOfD(pOfDGivenT, pOfT);
	calcPOfT(pOfDGivenT, pOfT, pOfD);
}

/*******************************************
*normalize assumes the known cells have a value of 1 or 0 and the others don't
*@param pOfT: where each cell k holds P(T_k), of size [length][width]
*@param remaining: the remaining number of special cells
*******************************************/
void normalize(float (*pOfT)[length][width], int remaining)
{
	float sum = 0;

	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			if (((*pOfT)[i][j] != 1.0) && ((*pOfT)[i][j] != 0.0))
				sum = sum + (*pOfT)[i][j];

	float normValue = remaining / sum;

	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			if (((*pOfT)[i][j] != 1.0) && ((*pOfT)[i][j] != 0.0))
				(*pOfT)[i][j] = (*pOfT)[i][j] * normValue;
}



int main(void) {
	return 0;
}