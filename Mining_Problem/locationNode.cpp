#include "locationNode.h"

double locationNode::basicHeurCostScale = defaultCostScale;
double locationNode::basicHeurProbScale = defaultProbScale;
double locationNode::advHeur1lvlScale = default1lvlScale;
double locationNode::advHeur2lvlScale = default2lvlScale;
double locationNode::advHeur3lvlScale = default3lvlScale;


locationNode::locationNode(int x, int y, double prob)
{
	this->position.x = x;
	this->position.y = y;
	this->prob = prob;
	this->basePosition.x = length + length / 2;
	this->basePosition.y = width / 2;
}


locationNode::~locationNode()
{
}

/*int locationNode::getCost() 
{
	return 2*manhDist(this->position, this->basePosition);
}*/

Position locationNode::getPosition()
{
	return this->position;
}

void locationNode::setPosition(Position position)
{
	this->position = position;
}

double locationNode::getProb()
{
	return this->prob;
}

void locationNode::setProb(double prob)
{
	this->prob = prob;
}

/*double locationNode::getBasicHeuristicValue()
{
	return 0;// (this->getCost())*(this->basicHeurCostScale) + (this->prob) * (this->basicHeurProbScale);
}*/

void locationNode::setBasicHeuristic(double costScaler, double probScaler)
{
	this->basicHeurCostScale = costScaler;
	this->basicHeurProbScale = probScaler;
}

bool locationNode::operator<(locationNode & rhs)
{
	return this->getBasicHeuristicValue() < rhs.getBasicHeuristicValue();
}
/*bool operator<(locationNode & lhs, locationNode & rhs)
{
	return lhs.getBasicHeuristicValue() < rhs.getBasicHeuristicValue();
}*/

bool compareLocNodes(locationNode a, locationNode b)
{
	return a.getBasicHeuristicValue() < b.getBasicHeuristicValue();
}