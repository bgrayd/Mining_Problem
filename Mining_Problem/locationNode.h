#pragma once
#include "mining_problem.h"

#define defaultCostScale -1
#define defaultProbScale 10
class locationNode
{
public:
	locationNode();
	~locationNode();
	int getCost();
	void setCost(int cost);
	Position getPosition();
	void setPosition(Position position);
	double getProb();
	void setProb(double prob);

	double getHeuristicValue();
	void setBasicHeuristic(double costScaler, double probScaler);

	Position position;
	double prob;
	int cost;

	double basicHeurCostScale = defaultCostScale;
	double basicHeurProbScale = defaultProbScale;
};

