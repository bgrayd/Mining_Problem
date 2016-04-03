#include "locationNode.h"



locationNode::locationNode()
{
}


locationNode::~locationNode()
{
}

int locationNode::getCost() 
{
	return this->cost;
}

void locationNode::setCost(int cost)
{
	this->cost = cost;
}

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

double locationNode::getHeuristicValue()
{
	return (this->cost)*(this->basicHeurCostScale) + (this->prob) * (this->basicHeurProbScale);
}

void locationNode::setBasicHeuristic(double costScaler, double probScaler)
{
	this->basicHeurCostScale = costScaler;
	this->basicHeurProbScale = probScaler;
}