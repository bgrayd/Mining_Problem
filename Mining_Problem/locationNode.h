#pragma once
#include "mining_problem.h"

#define defaultCostScale   -3
#define defaultProbScale	5
#define default1lvlScale	3
#define default2lvlScale	2
#define default3lvlScale	1


class locationNode
{
public:
	locationNode(int x, int y, double prob);
	~locationNode();

	int LUT1lvl[64] = {
		2, 3, 3, 3, 3, 3, 3, 2,
		3, 4, 4, 4, 4, 4, 4, 3,
		3, 4, 4, 4, 4, 4, 4, 3,
		3, 4, 4, 4, 4, 4, 4, 3,
		3, 4, 4, 4, 4, 4, 4, 3,
		3, 4, 4, 4, 4, 4, 4, 3,
		3, 4, 4, 4, 4, 4, 4, 3,
		2, 3, 3, 3, 3, 3, 3, 2 };

	int LUT2lvl[64] = {
		3, 4, 5, 5, 5, 5, 4, 3,
		4, 6, 7, 7, 7, 7, 7, 4,
		5, 7, 8, 8, 8, 8, 7, 5,
		5, 7, 8, 8, 8, 8, 7, 5,
		5, 7, 8, 8, 8, 8, 7, 5,
		5, 7, 8, 8, 8, 8, 7, 5,
		4, 7, 7, 7, 7, 7, 7, 4,
		3, 4, 5, 5, 5, 5, 4, 3 };

	int LUT3lvl[64] = {
		4, 5, 6, 7, 7, 6, 5, 4,
		5, 6, 8, 9, 10, 8, 6, 5,
		6, 8, 10, 10, 10, 10, 8, 6,
		7, 9, 10, 12, 12, 10, 10, 7,
		7, 9, 10, 12, 12, 10, 10, 7,
		6, 8, 10, 10, 10, 10, 8, 6,
		5, 6, 8, 9, 9, 8, 6, 5,
		4, 5, 6, 7, 7, 6, 5, 4 };
	
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
	double locationNode::getAdvancedHeuristicValue() const
	{
		double runningValue = this->getBasicHeuristicValue();
		int LutPos = this->position.x + (this->position.y*width);

		runningValue = runningValue + (advHeur1lvlScale*LUT1lvl[LutPos]);
		runningValue = runningValue + (advHeur2lvlScale*LUT2lvl[LutPos]);
		runningValue = runningValue + (advHeur3lvlScale*LUT3lvl[LutPos]);

		return runningValue;
	}
	void setBasicHeuristic(double costScaler, double probScaler);
	bool operator<(locationNode & rhs);
	friend bool operator<(const locationNode& lhs, const locationNode& rhs) {
		return lhs.getAdvancedHeuristicValue() < rhs.getAdvancedHeuristicValue();
	};

	Position position;
	double prob;

	static double basicHeurCostScale;// = defaultCostScale;
	static double basicHeurProbScale;// = defaultProbScale;
	static double advHeur1lvlScale;// = default1lvlScale;
	static double advHeur2lvlScale;// = default2lvlScale;
	static double advHeur3lvlScale;// = default3lvlScale;

	Position basePosition;
};

bool compareLocNodes(locationNode a, locationNode b);
/*bool operator<(const locationNode lhs, locationNode rhs) {
	return lhs.getBasicHeuristicValue() < rhs.getBasicHeuristicValue();
};*/

