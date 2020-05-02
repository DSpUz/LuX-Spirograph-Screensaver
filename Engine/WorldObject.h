
/*******************************************************************************************
*	Code and amendments by s0lly														   *
*	https://www.youtube.com/c/s0lly							                               *
*	https://s0lly.itch.io/																   *
*	https://www.instagram.com/s0lly.gaming/												   *
********************************************************************************************/

#pragma once

#include "Vec2.h"
#include "Colors.h"
#include <random>

class WorldObject
{
public:
	WorldObject(Vec2 in_loc,Vec2 in_oldVelocity,Vec2 in_velocity,float in_mass,float in_radius, int in_nodeID,Color in_c);

	
	
	static bool CheckCollision(Vec2& loc1, Vec2& loc2, float r1, float r2);
	void InverseVelX();
	void InverseVelY();
	const Vec2& GetLoc() const;
	Vec2& GetLoc();
	int GetLocX() const;
	int GetLocY() const;
	int GetnodeID() const;
	float GetMass() const;
	Vec2 GetVel() const;
	Vec2 GetOldVel() const;
	Vec2& GetVelRef();
	void SetLoc(Vec2 newloc);
	void SetVel(Vec2 newvel);
	void SetOldVel(Vec2 newvel);
	void SetNodeID(int index);
	Color GetColor() const;
	/*static void MergeObjects(WorldObject* worldObjectsPtr, int first, int second)
	{

		Vec2 newLoc = Vec2((worldObjectsPtr->loc[first].x * worldObjectsPtr->mass[first] + worldObjectsPtr->loc[second].x * worldObjectsPtr->mass[second]) / (worldObjectsPtr->mass[first] + worldObjectsPtr->mass[second]), (worldObjectsPtr->loc[first].y * worldObjectsPtr->mass[first] + worldObjectsPtr->loc[second].y * worldObjectsPtr->mass[second]) / (worldObjectsPtr->mass[first] + worldObjectsPtr->mass[second]));
		float newMass = worldObjectsPtr->mass[first] + worldObjectsPtr->mass[second];

		//float newAreaSqrd = worldObjectsPtr->radius[first] * worldObjectsPtr->radius[first] + worldObjectsPtr->radius[second] * worldObjectsPtr->radius[second];
		float newRadius = std::sqrt(newMass / (PI / 2.0f));
		//float newRadius = std::sqrt(newMass / PI);

		unsigned char newR = (unsigned char)(((float)worldObjectsPtr->color[first].GetR() * (worldObjectsPtr->mass[first]) + (float)worldObjectsPtr->color[second].GetR() * worldObjectsPtr->mass[second]) / (worldObjectsPtr->mass[first] + worldObjectsPtr->mass[second]));
		unsigned char newG = (unsigned char)(((float)worldObjectsPtr->color[first].GetG() * (worldObjectsPtr->mass[first]) + (float)worldObjectsPtr->color[second].GetG() * worldObjectsPtr->mass[second]) / (worldObjectsPtr->mass[first] + worldObjectsPtr->mass[second]));
		unsigned char newB = (unsigned char)(((float)worldObjectsPtr->color[first].GetB() * (worldObjectsPtr->mass[first]) + (float)worldObjectsPtr->color[second].GetB() * worldObjectsPtr->mass[second]) / (worldObjectsPtr->mass[first] + worldObjectsPtr->mass[second]));

		Color newColor = Color(newR, newG, newB);

		Vec2 newOldVelocity((worldObjectsPtr->oldVelocity[first] * worldObjectsPtr->mass[first] + worldObjectsPtr->oldVelocity[second] * worldObjectsPtr->mass[second]) / newMass);
		Vec2 newVelocity((worldObjectsPtr->velocity[first] * worldObjectsPtr->mass[first] + worldObjectsPtr->velocity[second] * worldObjectsPtr->mass[second]) / newMass);

		std::swap(worldObjectsPtr->loc[second], worldObjectsPtr->loc[worldObjectsPtr->currentAssignedObjects - 1]);
		std::swap(worldObjectsPtr->oldVelocity[second], worldObjectsPtr->oldVelocity[worldObjectsPtr->currentAssignedObjects - 1]);
		std::swap(worldObjectsPtr->velocity[second], worldObjectsPtr->velocity[worldObjectsPtr->currentAssignedObjects - 1]);
		std::swap(worldObjectsPtr->mass[second], worldObjectsPtr->mass[worldObjectsPtr->currentAssignedObjects - 1]);
		std::swap(worldObjectsPtr->radius[second], worldObjectsPtr->radius[worldObjectsPtr->currentAssignedObjects - 1]);
		std::swap(worldObjectsPtr->color[second], worldObjectsPtr->color[worldObjectsPtr->currentAssignedObjects - 1]);
		std::swap(worldObjectsPtr->nodeID[second], worldObjectsPtr->nodeID[worldObjectsPtr->currentAssignedObjects - 1]);

		worldObjectsPtr->currentAssignedObjects--;


		std::swap(worldObjectsPtr->loc[first], worldObjectsPtr->loc[worldObjectsPtr->currentAssignedObjects - 1]);
		std::swap(worldObjectsPtr->oldVelocity[first], worldObjectsPtr->oldVelocity[worldObjectsPtr->currentAssignedObjects - 1]);
		std::swap(worldObjectsPtr->velocity[first], worldObjectsPtr->velocity[worldObjectsPtr->currentAssignedObjects - 1]);
		std::swap(worldObjectsPtr->mass[first], worldObjectsPtr->mass[worldObjectsPtr->currentAssignedObjects - 1]);
		std::swap(worldObjectsPtr->radius[first], worldObjectsPtr->radius[worldObjectsPtr->currentAssignedObjects - 1]);
		std::swap(worldObjectsPtr->color[first], worldObjectsPtr->color[worldObjectsPtr->currentAssignedObjects - 1]);
		std::swap(worldObjectsPtr->nodeID[first], worldObjectsPtr->nodeID[worldObjectsPtr->currentAssignedObjects - 1]);

		worldObjectsPtr->currentAssignedObjects--;


		worldObjectsPtr->loc[worldObjectsPtr->currentAssignedObjects] = newLoc;
		worldObjectsPtr->oldVelocity[worldObjectsPtr->currentAssignedObjects] = newOldVelocity;
		worldObjectsPtr->velocity[worldObjectsPtr->currentAssignedObjects] = newVelocity;
		worldObjectsPtr->mass[worldObjectsPtr->currentAssignedObjects] = newMass;
		worldObjectsPtr->radius[worldObjectsPtr->currentAssignedObjects] = newRadius;
		worldObjectsPtr->color[worldObjectsPtr->currentAssignedObjects] = newColor;
		worldObjectsPtr->nodeID[worldObjectsPtr->currentAssignedObjects] = -1; // this should be irrelevant as is reset before used

		worldObjectsPtr->currentAssignedObjects++;
	}*/

private:
	Vec2 loc;
	Vec2 oldVelocity;
	Vec2 velocity;
	float mass;
	float radius;
	int nodeID;
	Color color;
};

