#include"Node.h"
void Node::FillWithObjectIndex(int index)
{
	ContainedObjectsIndices.push_back(index);
}

Vec2 Node::GetAveLoc() const
{
	return AveLoc;
}

float Node::GetMass() const
{
	return mass;
}

void Node::SetAveLoc(Vec2 LocAve)
{
	AveLoc = LocAve;
}

void Node::SetMass(float newmass)
{
	mass = newmass;
}

std::vector<int> Node::GetContainedObjInd() const
{
	return ContainedObjectsIndices;
}

