#include "WorldObject.h"

WorldObject::WorldObject(Vec2 in_loc, Vec2 in_oldVelocity, Vec2 in_velocity, float in_mass, float in_radius, int in_nodeID, Color in_c)
	:
	loc(in_loc),
	oldVelocity(in_oldVelocity),
	velocity(in_velocity),
	mass(in_mass),
	radius(in_radius),
	nodeID(in_nodeID),
	color(in_c)
{
}

bool WorldObject::CheckCollision(Vec2 & loc1, Vec2 & loc2, float r1, float r2)
 {
	 float radiusSqrd = (loc1.x - loc2.x) * (loc1.x - loc2.x) + (loc1.y - loc2.y) * (loc1.y - loc2.y);
	 float radiusCollideSqrd = (r1 + r2) * (r1 + r2);
	 return (radiusSqrd <= radiusCollideSqrd);
 }

void WorldObject::InverseVelX()
{
	velocity.x *= -1;
}

void WorldObject::InverseVelY()
{
	velocity.y *= -1;
}

const Vec2& WorldObject::GetLoc() const
{
	return loc;
}

 Vec2 & WorldObject::GetLoc()
 {
	 return loc;
 }

int WorldObject::GetLocX() const
{
	return int(loc.x);
}

int WorldObject::GetLocY() const
{
	return int(loc.y);
}

int WorldObject::GetnodeID() const
{
	return nodeID;
}

float WorldObject::GetMass() const
{
	return mass;
}

Vec2 WorldObject::GetVel() const
{
	return velocity;
}

Vec2 WorldObject::GetOldVel() const
{
	return oldVelocity;
}

Vec2 & WorldObject::GetVelRef()
{
	return velocity;
}

void WorldObject::SetLoc(Vec2 newloc)
{
	loc = newloc;
}

void WorldObject::SetVel(Vec2 newvel)
{
	velocity=newvel;
}

void WorldObject::SetOldVel(Vec2 newvel)
{
	oldVelocity = newvel;
}

void WorldObject::SetNodeID(int index)
{
	nodeID = index;
}

Color WorldObject::GetColor() const
{
	return color;
}

