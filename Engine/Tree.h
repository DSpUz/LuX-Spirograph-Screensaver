#pragma once
#include <assert.h>
#include "Node.h"
/*******************************************************************************************
*	Code and amendments by s0lly														   *
*	https://www.youtube.com/c/s0lly							                               *
*	https://s0lly.itch.io/																   *
*	https://www.instagram.com/s0lly.gaming/												   *
********************************************************************************************/


#include "Vec2.h"
#include "WorldObject.h"
#include <thread>

class Tree
{
public:
	void Init(int currentAssignedObjects)
	{
		topLeft = Vec2();
		botRight = Vec2();

		int lowestPowerOf4 = 1;
		numPlanes = 0;

		while (lowestPowerOf4 < currentAssignedObjects)
		{
			lowestPowerOf4 *= 4;
			numPlanes++;
		}

		TotalNumberOfNodes = 0;

		for (int p = 0; p < numPlanes; p++)
		{
			TotalNumberOfNodes += int(pow(4, p));//nodes are 4 segments of a plane(square that is split in 4 new squares, total number of nodes therefore equals this formula
		}

		nodeObjects.clear();
		nodeObjects = std::vector<Node>(TotalNumberOfNodes);
	}
	void Refresh(std::vector<WorldObject>& worldObjects, int number_of_Objects)
	{
		// Worldspace is the highest level space (equivalent to maxPlane). Each space has 4 qaudrants.
		// set worldObjects to detailed plane nodes

		topLeft = Vec2();
		botRight = Vec2();

		for (int i = 0; i < number_of_Objects; i++)
		{
			//calculates boundaries of quadrees top plane
			/*Conditional ternary operator ( ? ) from http://www.cplusplus.com/doc/tutorial/operators/
			The conditional operator evaluates an expression, returning one value if that expression evaluates to true,
			and a different one if the expression evaluates as false.Its syntax is :

			condition ? result1 : result2

				If condition is true, the entire expression evaluates to result1, and otherwise to result2.

				for example:
				7 == 5 ? 4 : 3     // evaluates to 3, since 7 is not equal to 5.
				7 == 5 + 2 ? 4 : 3   // evaluates to 4, since 7 is equal to 5+2.
				5 > 3 ? a : b      // evaluates to the value of a, since 5 is greater than 3.
				a > b ? a : b      // evaluates to whichever is greater, a or b.
				However in this case  https://www.geeksforgeeks.org/conditional-or-ternary-operator-in-c-c/ variant is applied
				where

				variable = Expression1 ? Expression2 : Expression3

				It can be visualized as if(Expression1)
				{
				variable = Expression2;
				}
				else
				{
				 variable = Expression3;
				}
				*/
			topLeft.x = topLeft.x < worldObjects[i].GetLocX() ? topLeft.x : worldObjects[i].GetLocX() - 1.0f;
			topLeft.y = topLeft.y < worldObjects[i].GetLocY() ? topLeft.y : worldObjects[i].GetLocY() - 1.0f;
			botRight.x = botRight.x > worldObjects[i].GetLocX() ? botRight.x : worldObjects[i].GetLocX() + 1.0f;
			botRight.y = botRight.y > worldObjects[i].GetLocY() ? botRight.y : worldObjects[i].GetLocY() + 1.0f;
		}

		treeWidth = botRight.x - topLeft.x;
		treeHeight = botRight.y - topLeft.y;

		// We want some higher power of 4 than current worldObjects to get fine resolution on calculations

		nodeObjects = std::vector<Node>(int(pow(4, numPlanes)));

		int LowestPlaneDim = int(pow(2, numPlanes - 1));//for example if field is 16x16 then lowest plane would have dimension of 16/(2^3) = 2 in relation to field width
		float LowestPlaneWidth =  treeWidth / (float)LowestPlaneDim;
		float LowestPlaneHeight = treeHeight / (float)LowestPlaneDim;

				for (int i = 0; i < number_of_Objects; i++)
				{
					int x = int((worldObjects[i].GetLocX() - topLeft.x )/ LowestPlaneWidth);
					int y = int((worldObjects[i].GetLocY() - topLeft.y )/ LowestPlaneHeight);
					
					int detailedNode = y * int(treeWidth/LowestPlaneWidth) + x;
					assert(detailedNode < nodeObjects.size());
					worldObjects[i].SetNodeID(detailedNode);
					nodeObjects[detailedNode].FillWithObjectIndex(i);


					nodeObjects[detailedNode].SetAveLoc(nodeObjects[detailedNode].GetAveLoc() + worldObjects[i].GetLoc() * worldObjects[i].GetMass());//Set AveLoc
					nodeObjects[detailedNode].SetMass(nodeObjects[detailedNode].GetMass() + worldObjects[i].GetMass());//Set Mass

					// we've loaded in lowest plane, now work up

					int currX = x;
					int currY = y;
					int numOfPriorPlaneNodes = 0;

					Vec2 locTimesMass = worldObjects[i].GetLoc() * worldObjects[i].GetMass();

					for (int p = 1; p <numPlanes - 1; p++)
					{
						numOfPriorPlaneNodes += int(pow(4, numPlanes - p));

						currX /= 2;
						currY /= 2;

						int planeNode = numOfPriorPlaneNodes + currY * int(pow(2, (numPlanes - p - 1))) + currX;

						nodeObjects[planeNode].SetAveLoc(nodeObjects[planeNode].GetAveLoc() + locTimesMass);
						nodeObjects[planeNode].SetMass( nodeObjects[planeNode].GetMass() + worldObjects[i].GetMass());
					}
				}

		for (int n = 0; n < TotalNumberOfNodes - 1; n++)
		{
			if (nodeObjects[n].GetMass() > 0.0f)
			{
				nodeObjects[n].SetAveLoc(nodeObjects[n].GetAveLoc() / nodeObjects[n].GetMass());//Recalculate Average Location by divison
			}
		}
	}
	bool ApplyGravityToFirst(Vec2& locFirst, float massFirst, Vec2& velocityFirst,
							Vec2& locSecond, float massSecond, float dt, bool isNode);
	void ApplyForce(Vec2& velocity, float mass, Vec2 in_force, float dt);
	int GetPlaneNum() const;
private://private classes 

	public:
		std::vector<Node>& GetNodeObjRef();
		void RecursivePlaneQuadrantCheckAndApplyGravity(std::vector<WorldObject>& worldObjects,
			int worldObjIndex, int maxPlanes, int priorPlane,
			std::vector<Node>& nodeObjects,int priorX, int priorY, float dt) {
			int priorPlaneNodeStart = 0;
			int quadrantPlaneNodeStart = 0;

			for (int p = maxPlanes - priorPlane; p < maxPlanes; p++)
			{
				priorPlaneNodeStart += int(pow(4, p));
			}
			// number of quadrants on each level is one term less of power series
			quadrantPlaneNodeStart = priorPlaneNodeStart - int(pow(4, maxPlanes - priorPlane));
			/*for (int p = maxPlanes - priorPlane + 1; p < maxPlanes; p++)
			{
				quadrantPlaneNodeStart += int(pow(4, p));
			}*/

			int newXStart = priorX * 2;
			int newYStart = priorY * 2;
			int newNodeDim = int(pow(2, maxPlanes - priorPlane));// at each quadtree plane level we have different node dimenensions

			int worldObjNodeIDDim = int(pow(2, maxPlanes - 1) + 0.5f);//power function returns a double but when converted to int 0.5 equals 0
			assert(worldObjNodeIDDim != 0);
			assert(priorPlane - 1 >= 0);
			int worldObjNodeIDX = (worldObjects[worldObjIndex].GetnodeID() % worldObjNodeIDDim) / int(pow(2, priorPlane - 1));
			int worldObjNodeIDY = (worldObjects[worldObjIndex].GetnodeID() / worldObjNodeIDDim) / int(pow(2, priorPlane - 1));

			for (int y = newYStart; y < newYStart + 2; y++)//This code runs through 4 sectors of a quadrant
			{
				for (int x = newXStart; x < newXStart + 2; x++)
				{
					int nodeIndex = quadrantPlaneNodeStart + y * newNodeDim + x;//index of node mass array
					bool ObjInNode = (worldObjNodeIDX == x && worldObjNodeIDY == y);
					if (nodeObjects[nodeIndex].GetMass() > 0.0f)
					{
						if (ObjInNode)
						{
							if (priorPlane == 1)//this is the recursion termination expression parameter meaning it is true when current plane has reached 0
							{
								for (int t = 0; t < nodeObjects[nodeIndex].GetContainedObjInd().size(); t++)
								{
									int targetWorldObject = nodeObjects[nodeIndex].GetContainedObjInd()[t];
									if (worldObjIndex != targetWorldObject)
									{
										ApplyGravityToFirst(worldObjects[worldObjIndex].GetLoc(), worldObjects[worldObjIndex].GetMass(), worldObjects[worldObjIndex].GetVelRef(),
											worldObjects[targetWorldObject].GetLoc(), worldObjects[targetWorldObject].GetMass(), dt, false);
									}
								}
							}
							else
							{
								RecursivePlaneQuadrantCheckAndApplyGravity(worldObjects, worldObjIndex, maxPlanes, priorPlane - 1,
									nodeObjects, x, y, dt);
							}
						}
						else
						{
							if (!ApplyGravityToFirst(worldObjects[worldObjIndex].GetLoc(), worldObjects[worldObjIndex].GetMass(), worldObjects[worldObjIndex].GetVelRef(),
								nodeObjects[nodeIndex].GetAveLoc(), nodeObjects[nodeIndex].GetMass(), dt, true))
							{
								if (!(priorPlane == 1))
								{
									RecursivePlaneQuadrantCheckAndApplyGravity(worldObjects, worldObjIndex, maxPlanes, priorPlane - 1,
									nodeObjects, x, y, dt);
								}
								else
								{
									for (int t = 0; t < nodeObjects[nodeIndex].GetContainedObjInd().size(); t++)
									{
										int targetWorldObject = nodeObjects[nodeIndex].GetContainedObjInd()[t];
										ApplyGravityToFirst(worldObjects[worldObjIndex].GetLoc(), worldObjects[worldObjIndex].GetMass(), worldObjects[worldObjIndex].GetVelRef(),
											worldObjects[targetWorldObject].GetLoc(), worldObjects[targetWorldObject].GetMass(), dt, false);
									}
								}
							}
						}
					}
				}
			}
		}
private://private tree variables
	std::vector<Node> nodeObjects;
	int TotalNumberOfNodes = 0;
	int numPlanes = 0;

	Vec2 topLeft;
	Vec2 botRight;

	float treeWidth;
	float treeHeight;
};