#pragma once
#include <vector>
#include"Vec2.h"
class Node {
public:
	void FillWithObjectIndex(int index);
	Vec2 GetAveLoc() const;
	float GetMass() const;
	void SetAveLoc(Vec2 LocAve);
	void SetMass(float newmass);
	std::vector<int> GetContainedObjInd() const;
private:
	std::vector<int> ContainedObjectsIndices;
	Vec2 Loc;
	Vec2 AveLoc;//Location times mass
	float mass;
};
