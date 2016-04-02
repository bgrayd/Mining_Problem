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
	float getProb();
	void setProb(float prob);

	float getHeuristicValue();
	void setBasicHeuristic(float costScaler, float probScaler);

	Position position;
	float prob;
	int cost;

	float basicHeurCostScale = defaultCostScale;
	float basicHeurProbScale = defaultProbScale;
};

