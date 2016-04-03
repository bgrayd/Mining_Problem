#pragma once
#include "mining_problem.h"

#define defaultCostScale -1
#define defaultProbScale 10
class locationNode
{
public:
	locationNode(int x, int y, double prob);
	~locationNode();
	int getCost();
	Position getPosition();
	void setPosition(Position position);
	double getProb();
	void setProb(double prob);

	double getBasicHeuristicValue();
	void setBasicHeuristic(double costScaler, double probScaler);
	bool operator<(locationNode & rhs);

	Position position;
	double prob;

	double basicHeurCostScale = defaultCostScale;
	double basicHeurProbScale = defaultProbScale;

	Position basePosition;
};

bool compareLocNodes(locationNode a, locationNode b);
bool operator<(const locationNode & lhs, const locationNode & rhs);

