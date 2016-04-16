#pragma once
#include "mining_problem.h"

#define defaultCostScale -1
#define defaultProbScale 0
class locationNode
{
public:
	locationNode(int x, int y, double prob);
	~locationNode();
	int getCost() const
	{
		return 2 * manhDist(this->position, this->basePosition);
	};
	Position getPosition();
	void setPosition(Position position);
	double getProb();
	void setProb(double prob);

	//double getBasicHeuristicValue();
	double locationNode::getBasicHeuristicValue() const
	{
		return (this->getCost())*(this->basicHeurCostScale) + (this->prob) * (this->basicHeurProbScale);
	}
	void setBasicHeuristic(double costScaler, double probScaler);
	bool operator<(locationNode & rhs);
	friend bool operator<(const locationNode& lhs, const locationNode& rhs) {
		return lhs.getBasicHeuristicValue() < rhs.getBasicHeuristicValue();
	};

	Position position;
	double prob;

	double basicHeurCostScale = defaultCostScale;
	double basicHeurProbScale = defaultProbScale;

	Position basePosition;
};

bool compareLocNodes(locationNode a, locationNode b);
/*bool operator<(const locationNode lhs, locationNode rhs) {
	return lhs.getBasicHeuristicValue() < rhs.getBasicHeuristicValue();
};*/

