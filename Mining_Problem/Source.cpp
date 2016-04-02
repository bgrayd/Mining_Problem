#include <stdlib.h> 
#include <queue>
#include "mining_problem.h"




/********************************************
*returns the manhattan distance between two points
*********************************************/
int manhDist(int x1, int y1, int x2, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}

/********************************************
*returns the manhattan distance between two points
*********************************************/
int manhDist(Position pos1, Position pos2)
{
	manhDist(pos1.x, pos1.y, pos2.x, pos2.y);
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

/*******************************************
*calcPOfDGivenT P(d_i | T_k)
*@param pOfDGivenT: a 2D array of size[length][width] that the values will be stored in
*@param posChecked: the position of the new observation
*@param special: is the newly checked spot a special valued spot
*******************************************/
void calcPOfDGivenT(float(*pOfDGivenT)[length][width], Position posChecked, bool special)
{
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			(*pOfDGivenT)[i][j] = 0;

	std::queue<Position> myQueue;
	Position currentPos, nextPos;
	float adjProb = (special) ? probAdjYgivenY : probAdjYgivenN;
	currentPos = posChecked;

	nextPos.x = currentPos.x - 1;
	nextPos.y = currentPos.y - 1;
	if ((nextPos.x >= 0) && (nextPos.y >= 0) && (nextPos.x < length) && (nextPos.y < width))
	{
		(*pOfDGivenT)[nextPos.x][nextPos.y] = (*pOfDGivenT)[nextPos.x][nextPos.y] + adjProb;
		myQueue.push(nextPos);
	}
	nextPos.x = currentPos.x + 1;
	nextPos.y = currentPos.y - 1;
	if ((nextPos.x >= 0) && (nextPos.y >= 0) && (nextPos.x < length) && (nextPos.y < width))
	{
		(*pOfDGivenT)[nextPos.x][nextPos.y] = (*pOfDGivenT)[nextPos.x][nextPos.y] + adjProb;
		myQueue.push(nextPos);
	}
	nextPos.x = currentPos.x - 1;
	nextPos.y = currentPos.y + 1;
	if ((nextPos.x >= 0) && (nextPos.y >= 0) && (nextPos.x < length) && (nextPos.y < width))
	{
		(*pOfDGivenT)[nextPos.x][nextPos.y] = (*pOfDGivenT)[nextPos.x][nextPos.y] + adjProb;
		myQueue.push(nextPos);
	}
	nextPos.x = currentPos.x + 1;
	nextPos.y = currentPos.y + 1;
	if ((nextPos.x >= 0) && (nextPos.y >= 0) && (nextPos.x < length) && (nextPos.y < width))
	{
		(*pOfDGivenT)[nextPos.x][nextPos.y] = (*pOfDGivenT)[nextPos.x][nextPos.y] + adjProb;
		myQueue.push(nextPos);
	}


	while (!myQueue.empty)
	{
		currentPos = myQueue.front();
		myQueue.pop();
		adjProb = probAdjYgivenY * (*pOfDGivenT)[currentPos.x][currentPos.y];

		nextPos.x = currentPos.x - 1;
		nextPos.y = currentPos.y - 1;
		if ((nextPos.x >= 0) && (nextPos.y >= 0) && (nextPos.x < length) && (nextPos.y < width) && (manhDist(nextPos, posChecked) > manhDist(currentPos, posChecked)))
		{
			(*pOfDGivenT)[nextPos.x][nextPos.y] = (*pOfDGivenT)[nextPos.x][nextPos.y] + adjProb;
			myQueue.push(nextPos);
		}
		nextPos.x = currentPos.x + 1;
		nextPos.y = currentPos.y - 1;
		if ((nextPos.x >= 0) && (nextPos.y >= 0) && (nextPos.x < length) && (nextPos.y < width) && (manhDist(nextPos, posChecked) > manhDist(currentPos, posChecked)))
		{
			(*pOfDGivenT)[nextPos.x][nextPos.y] = (*pOfDGivenT)[nextPos.x][nextPos.y] + adjProb;
			myQueue.push(nextPos);
		}
		nextPos.x = currentPos.x - 1;
		nextPos.y = currentPos.y + 1;
		if ((nextPos.x >= 0) && (nextPos.y >= 0) && (nextPos.x < length) && (nextPos.y < width) && (manhDist(nextPos, posChecked) > manhDist(currentPos, posChecked)))
		{
			(*pOfDGivenT)[nextPos.x][nextPos.y] = (*pOfDGivenT)[nextPos.x][nextPos.y] + adjProb;
			myQueue.push(nextPos);
		}
		nextPos.x = currentPos.x + 1;
		nextPos.y = currentPos.y + 1;
		if ((nextPos.x >= 0) && (nextPos.y >= 0) && (nextPos.x < length) && (nextPos.y < width) && (manhDist(nextPos, posChecked) > manhDist(currentPos, posChecked)))
		{
			(*pOfDGivenT)[nextPos.x][nextPos.y] = (*pOfDGivenT)[nextPos.x][nextPos.y] + adjProb;
			myQueue.push(nextPos);
		}

	}


}



int main(void) {
	return 0;
}