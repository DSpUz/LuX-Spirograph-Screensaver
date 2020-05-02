#include "Tree.h"

bool Tree::ApplyGravityToFirst(Vec2 & locFirst, float massFirst, Vec2 & velocityFirst, Vec2 & locSecond, float massSecond, float dt, bool isNode)
{
		Vec2 vectorFromFirstToSecond = locSecond - locFirst;

		float radiusSqrd = GetVec2Magnitude(vectorFromFirstToSecond);
		//radiusSqrd = radiusSqrd < minRadiusSqrdAllowed ? minRadiusSqrdAllowed : radiusSqrd;

		if (radiusSqrd > 0.001f) // Ensures that infinity speed is not possible
		{
			float gravityMagnitude = (GRAV_CONST * massFirst * massSecond) / radiusSqrd; // The constant can be changed to effect all objects masses

			Vec2 gravOnFirstToSecond = GetNormalizedVec2(vectorFromFirstToSecond) * gravityMagnitude;

			if (isNode)
			{
				if (gravityMagnitude < NODE_GRAV_THRESHOLD)
				{
					ApplyForce(velocityFirst, massFirst, gravOnFirstToSecond, dt);
					return true;
				}
				else
				{
					return false;
				}

			}
			else
			{
				ApplyForce(velocityFirst, massFirst, gravOnFirstToSecond, dt);
				return true;
			}
		}
		else{
			return false;
		}
}

void Tree::ApplyForce(Vec2 & velocity, float mass, Vec2 in_force, float dt)
{
	velocity = velocity + (in_force * dt) / mass;
}

int Tree::GetPlaneNum() const
{
	return numPlanes;
}

std::vector<Node>& Tree::GetNodeObjRef()
{
	return nodeObjects;
}


