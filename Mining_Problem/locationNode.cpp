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

float locationNode::getProb()
{
	return this->prob;
}

void locationNode::setProb(float prob)
{
	this->prob = prob;
}

float locationNode::getHeuristicValue()
{
	return (this->cost)*(this->basicHeurCostScale) + (this->prob) * (this->basicHeurProbScale);
}

void locationNode::setBasicHeuristic(float costScaler, float probScaler)
{
	this->basicHeurCostScale = costScaler;
	this->basicHeurProbScale = probScaler;
}