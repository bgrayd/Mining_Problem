#include <stdlib.h> 
#include <queue>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include "mining_problem.h"
#include "locationNode.h"

using namespace std;

#define DEFAULTINPUTFILENAME "input.txt"
#define DEFAULTOUTPUTFILENAME "outputFile.txt"


double probAdjYgivenY = defaultProbAdjYgivenY;
double probAdjYgivenN = defaultProbAdjYgivenN;




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
	return manhDist(pos1.x, pos1.y, pos2.x, pos2.y);
}

/*******************************************
*calcPOfD calculates the P(d_i)
*@param pOfDGivenT: where each cell k holds the value P(d_i | T_k), of size [length][width]
*@param pOfT: where each cell k holds P(T_k), of size [length][width]
*@return: the value P(d_i)
*******************************************/
double calcPOfD(double(*pOfDGivenT)[length][width], double(*pOfT)[length][width])
{
	double runningPOfD = 0;

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
void calcPOfT(double(*pOfDGivenT)[length][width], double(*pOfT)[length][width], double pOfD)
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
void calcPOfT(double(*pOfDGivenT)[length][width], double(*pOfT)[length][width])
{
	double pOfD = calcPOfD(pOfDGivenT, pOfT);
	calcPOfT(pOfDGivenT, pOfT, pOfD);
}

/*******************************************
*normalize assumes the known cells have a value of 1 or 0 and the others don't
*@param pOfT: where each cell k holds P(T_k), of size [length][width]
*@param remaining: the remaining number of special cells
*******************************************/
void normalize(double(*pOfT)[length][width], int remaining)
{
	double sum = 0;

	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			if (((*pOfT)[i][j] != 1.0) && ((*pOfT)[i][j] != 0.0))
				sum = sum + (*pOfT)[i][j];

	double normValue = remaining / sum;

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
void calcPOfDGivenT(double(*pOfDGivenT)[length][width], Position posChecked, bool special)
{
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			(*pOfDGivenT)[i][j] = 0;

	std::queue<Position> myQueue;
	Position currentPos, nextPos;
	double adjProb = (special) ? probAdjYgivenY : probAdjYgivenN;
	currentPos = posChecked;

	nextPos.x = currentPos.x - 1;
	nextPos.y = currentPos.y;
	if ((nextPos.x >= 0) && (nextPos.y >= 0) && (nextPos.x < length) && (nextPos.y < width))
	{
		(*pOfDGivenT)[nextPos.x][nextPos.y] = (*pOfDGivenT)[nextPos.x][nextPos.y] + adjProb;
		myQueue.push(nextPos);
	}
	nextPos.x = currentPos.x + 1;
	nextPos.y = currentPos.y;
	if ((nextPos.x >= 0) && (nextPos.y >= 0) && (nextPos.x < length) && (nextPos.y < width))
	{
		(*pOfDGivenT)[nextPos.x][nextPos.y] = (*pOfDGivenT)[nextPos.x][nextPos.y] + adjProb;
		myQueue.push(nextPos);
	}
	nextPos.x = currentPos.x;
	nextPos.y = currentPos.y - 1;
	if ((nextPos.x >= 0) && (nextPos.y >= 0) && (nextPos.x < length) && (nextPos.y < width))
	{
		(*pOfDGivenT)[nextPos.x][nextPos.y] = (*pOfDGivenT)[nextPos.x][nextPos.y] + adjProb;
		myQueue.push(nextPos);
	}
	nextPos.x = currentPos.x;
	nextPos.y = currentPos.y + 1;
	if ((nextPos.x >= 0) && (nextPos.y >= 0) && (nextPos.x < length) && (nextPos.y < width))
	{
		(*pOfDGivenT)[nextPos.x][nextPos.y] = (*pOfDGivenT)[nextPos.x][nextPos.y] + adjProb;
		myQueue.push(nextPos);
	}


	while (!myQueue.empty())
	{
		currentPos = myQueue.front();
		myQueue.pop();
		adjProb = probAdjYgivenY * (*pOfDGivenT)[currentPos.x][currentPos.y];

		nextPos.x = currentPos.x - 1;
		nextPos.y = currentPos.y;
		if ((nextPos.x >= 0) && (nextPos.y >= 0) && (nextPos.x < length) && (nextPos.y < width) && (manhDist(nextPos, posChecked) > manhDist(currentPos, posChecked)))
		{
			(*pOfDGivenT)[nextPos.x][nextPos.y] = (*pOfDGivenT)[nextPos.x][nextPos.y] + adjProb;
			myQueue.push(nextPos);
		}
		nextPos.x = currentPos.x + 1;
		nextPos.y = currentPos.y;
		if ((nextPos.x >= 0) && (nextPos.y >= 0) && (nextPos.x < length) && (nextPos.y < width) && (manhDist(nextPos, posChecked) > manhDist(currentPos, posChecked)))
		{
			(*pOfDGivenT)[nextPos.x][nextPos.y] = (*pOfDGivenT)[nextPos.x][nextPos.y] + adjProb;
			myQueue.push(nextPos);
		}
		nextPos.x = currentPos.x;
		nextPos.y = currentPos.y - 1;
		if ((nextPos.x >= 0) && (nextPos.y >= 0) && (nextPos.x < length) && (nextPos.y < width) && (manhDist(nextPos, posChecked) > manhDist(currentPos, posChecked)))
		{
			(*pOfDGivenT)[nextPos.x][nextPos.y] = (*pOfDGivenT)[nextPos.x][nextPos.y] + adjProb;
			myQueue.push(nextPos);
		}
		nextPos.x = currentPos.x;
		nextPos.y = currentPos.y + 1;
		if ((nextPos.x >= 0) && (nextPos.y >= 0) && (nextPos.x < length) && (nextPos.y < width) && (manhDist(nextPos, posChecked) > manhDist(currentPos, posChecked)))
		{
			(*pOfDGivenT)[nextPos.x][nextPos.y] = (*pOfDGivenT)[nextPos.x][nextPos.y] + adjProb;
			myQueue.push(nextPos);
		}

	}


}


/*******************************************
*calcPOfD calculates the P(T_j)^1 = P(T_j | d_i), does the calculation in place
*@param pOfDGivenT: where each cell k holds the value P(d_i | T_k), of size [length][width]
*@param pOfT: where each cell k holds P(T_k), of size [length][width]
*@param pOfD: P(d)
*******************************************/
void updatePOfT(double(*pOfT)[length][width], Position posChecked, bool special, int remaining)
{
	(*pOfT)[posChecked.x][posChecked.y] = (special) ? 1.0 : 0.0;

	double pOfDGivenT[length][width];
	calcPOfDGivenT(&pOfDGivenT, posChecked, special);

	double pOfD = calcPOfD(&pOfDGivenT, pOfT);

	calcPOfT(&pOfDGivenT, pOfT, pOfD);

	normalize(pOfT, remaining);

	(*pOfT)[posChecked.x][posChecked.y] = (special) ? 1.0 : 0.0;

}

int run(bool(*answers)[length][width], int numSpecial) {
	double pOfT[length][width];
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			pOfT[i][j] = (numSpecial * 1.0) / (length*width*1.0); //normalize
		}
	}

	int currentGas = startingGas;
	int currentNumSpecial = numSpecial;
	int currentReward = 0;
	bool visitedNodes[length][width];
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			visitedNodes[i][j] = false;

	while (1) {
		// Init the queue
		std::priority_queue<locationNode, std::vector<locationNode>, std::less<locationNode>> prioQueue;

		// Calculate gas costs
		for (int i = 0; i < length; i++) {
			for (int j = 0; j < width; j++) {
				locationNode ln = locationNode(i, j, pOfT[i][j]);
				if (currentGas > ln.getCost() && !visitedNodes[i][j]) {
					prioQueue.push(ln);
				}
			}
		}
		// Check to see if we have gas to get anywhere
		if (prioQueue.empty()) {
			break;
		}

		// Calculate new gas and reward
		locationNode chosenOption = prioQueue.top();
		visitedNodes[chosenOption.position.x][chosenOption.position.y] = true;
		currentGas = currentGas - chosenOption.getCost();
		if ((*answers)[chosenOption.position.x][chosenOption.position.y] == true) {
			currentReward = currentReward + baseReward + addedReward;
			currentNumSpecial = currentNumSpecial - 1;
		}
		else {
			currentReward = currentReward + baseReward;
		}

		//Update probibilities
		updatePOfT(&pOfT, chosenOption.position, (*answers)[chosenOption.position.x][chosenOption.position.y], currentNumSpecial);
	}

	return currentReward;
}

int main(int argc, char** argv) {
	fstream inFile;
	char c;
	string currentLine, toBeWritten;

	if (argc == 3)
	{
		/*sscanf_s(argv[1], "%lf", &locationNode::basicHeurCostScale);
		sscanf_s(argv[2], "%lf", &locationNode::basicHeurProbScale);*/
		locationNode::basicHeurCostScale = atof(argv[1]);
		locationNode::basicHeurProbScale = atof(argv[2]);
	}
	else if(argc == 6)// argc == 6
	{
		/*sscanf_s(argv[1], "%lf", &locationNode::basicHeurCostScale);
		sscanf_s(argv[2], "%lf", &locationNode::basicHeurProbScale);
		sscanf_s(argv[3], "%lf", &locationNode::advHeur1lvlScale);
		sscanf_s(argv[4], "%lf", &locationNode::advHeur2lvlScale);
		sscanf_s(argv[5], "%lf", &locationNode::advHeur3lvlScale);*/
		locationNode::basicHeurCostScale = atof(argv[1]);
		locationNode::basicHeurProbScale = atof(argv[2]);
		locationNode::advHeur1lvlScale = atof(argv[3]);
		locationNode::advHeur2lvlScale = atof(argv[4]);
		locationNode::advHeur3lvlScale = atof(argv[5]);
	}

	inFile.open(DEFAULTINPUTFILENAME, ios::in | ios::app);

	int count = 0;
	while (true)
	{
		c = inFile.peek();
		if (c == EOF)
			break;
		count++;
		bool answers[length][width];
		int numSpecial = 0;

		for (int i = 0; i < 8; i++)
		{
			getline(inFile, currentLine);
			for (int j = 0; j < 8; j++)
			{
				answers[i][j] = (currentLine[j] == '1') ? true : false;
				numSpecial += (currentLine[j] == '1') ? 1 : 0;
			}
		}

		getline(inFile, currentLine);
		probAdjYgivenY = atof(currentLine.c_str());
		getline(inFile, currentLine);
		probAdjYgivenN = atof(currentLine.c_str());

		c = inFile.peek();
		if (c != EOF)
			getline(inFile, currentLine);


		cout << run(&answers, numSpecial)<< "~";
	}
	inFile.close();
	return 0;
}

