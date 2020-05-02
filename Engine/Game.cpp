/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/

 /*******************************************************************************************
 *	Code and amendments by s0lly														   *
 *	https://www.youtube.com/c/s0lly							                               *
 *	https://s0lly.itch.io/																   *
 *	https://www.instagram.com/s0lly.gaming/												   *
 ********************************************************************************************/





#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd,wnd.GetHorizRes(),wnd.GetVertRes()),
	keysPressedLastFrame(false),
	ClonedOnce(false),
	ExplodedOnce(false),
	treeInitialised(false)
{
// Initialise objects
	//gfx.InitializeScreenDimensions();
	start = std::chrono::steady_clock::now();
	star.Init({ 400,300 }, 200.0f, 1.0f, 0, 0.04f, Colors::Green);
	stars.push_back(star);
}

void Game::Go()
{


	gfx.BeginFrame();

	ProcessInput();
	UpdateModel();
	ComposeFrame();

	gfx.EndFrame();

	

	

	
}

void Game::ProcessInput()
{}

void Game::DoUserInput()
{
	if (!keysPressedLastFrame) {
		if (wnd.mouse.LeftIsPressed())
		{
			keysPressedLastFrame = true;
			for (size_t i = 0; i < stars.size(); i++) {
				if (!ClonedOnce) {
					if (sqrt((float)((stars[i].GetPos().x - wnd.mouse.GetPosX())*(stars[i].GetPos().x - wnd.mouse.GetPosX()) + (stars[i].GetPos().y - wnd.mouse.GetPosY())*(stars[i].GetPos().y - wnd.mouse.GetPosY()))) < stars[i].GetSize())
					{
						star.Init(stars[i].GetPos(), stars[i].GetSize()*0.75f, stars[i].GetMovingAngle() - M_PI_4, stars[i].GetRotAngle(), stars[i].GetRotSpd()*1.1f, stars[i].GetCol());
						stars.push_back(star);
						star.Init(stars[i].GetPos(), stars[i].GetSize()*0.75f, stars[i].GetMovingAngle() + M_PI_4, stars[i].GetRotAngle(), stars[i].GetRotSpd()*1.1f, stars[i].GetCol());
						stars.push_back(star);
						stars.erase(stars.begin() + i);
						ClonedOnce = true;
					}
				}
			}
		}
		else if (wnd.mouse.RightIsPressed()) {
			keysPressedLastFrame = true;
			std::mt19937 rng;
			std::uniform_int_distribution<int> massDist(0, 10000);
			for (size_t i = 0; i < stars.size(); i++) {
				if (!ExplodedOnce) {
					if (sqrt((float)((stars[i].GetPos().x - wnd.mouse.GetPosX())*(stars[i].GetPos().x - wnd.mouse.GetPosX()) + (stars[i].GetPos().y - wnd.mouse.GetPosY())*(stars[i].GetPos().y - wnd.mouse.GetPosY()))) < stars[i].GetSize())
					{
						std::uniform_int_distribution<int> ObjDist(int(-(stars[i].GetSize())/2),int( stars[i].GetSize() )/ 2);
						for (int j = 0; j < int(stars[i].GetSize()); j++) {
							WorldObject init_object = { Vec2{ float(stars[i].GetPos().x + ObjDist(rng)),float(stars[i].GetPos().y + ObjDist(rng)) } ,Vec2{0.0f,0.0f},Vec2{float(ObjDist(rng)),float(ObjDist(rng))},float(massDist(rng)),1.0f,0,Colors::Green };
							worldObjects.push_back(init_object);
						}
						stars.erase(stars.begin() + i);
						ExplodedOnce = true;
						if (!treeInitialised) {
							tree.Init(int(worldObjects.size()));
							treeInitialised = true;}
					}
				}
			}
		}
		else if (wnd.kbd.KeyIsPressed(VK_SPACE)) {
			keysPressedLastFrame = true;
			star.Init({ 400,300 }, 200.0f, 1.0f, 0, 0.04f, Colors::Green);
			stars.push_back(star);
		}
		else if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
			wnd.Kill();
		}
	}
	else if (!wnd.mouse.LeftIsPressed() && !wnd.mouse.RightIsPressed()&&!wnd.kbd.KeyIsPressed(VK_SPACE)&&!wnd.kbd.KeyIsPressed(VK_RETURN)) {
		keysPressedLastFrame = false;
		ClonedOnce = false;
		ExplodedOnce = false;
	}
}

void Game::UpdateModel()
{
	DoUserInput();
	for (size_t i = 0; i < stars.size(); i++) {
		stars[i].Update(gfx);
	}
	tree.Refresh(worldObjects,int(worldObjects.size()));

	// Algorithm approach:
	//
	// for each object:
	// we check the first level of quadrants
	//
	// if the quadrant has a total mass vs distance at some ratio, check its quadrants for further examination
	// or if the quadrant contains the particle itself, check its quadrants
	//if the quadrant is at the highest level of resolution, use that quadrant's gravity
	//
	// else, apply that quadrant's gravity to the object in question
	//
	// lastly, for all objects in the quadrant of the object itself (if any), process each object individually

	for (int i = 0; i < int(worldObjects.size()); i++)
	{
		worldObjects[i].SetOldVel(worldObjects[i].GetVel());
	}


	// we will want to check the topmost quadrant first
	int currentPlane = tree.GetPlaneNum() - 1;

	for (int i = 0; i < int(worldObjects.size()); i++){
		tree.RecursivePlaneQuadrantCheckAndApplyGravity(worldObjects,i, tree.GetPlaneNum(), tree.GetPlaneNum() - 1,
		tree.GetNodeObjRef(), 0, 0, dt);
		}
			
	


	
	for (int i = 0; i < int(worldObjects.size()); i++)
	{
		worldObjects[i].SetLoc(worldObjects[i].GetLoc() + ((worldObjects[i].GetOldVel() + worldObjects[i].GetVel())*dt*0.5f));
		if (worldObjects[i].GetLoc().x < 0) {
			worldObjects[i].GetLoc().x = 0;
			worldObjects[i].InverseVelX();
		}
		if (worldObjects[i].GetLoc().x > gfx.GetScreenWidth()) {
			worldObjects[i].GetLoc().x = float(gfx.GetScreenWidth() - 1);
			worldObjects[i].InverseVelX();
		}
		if (worldObjects[i].GetLoc().y < 0) {
			worldObjects[i].GetLoc().y = 0;
			worldObjects[i].InverseVelY();
		}
		if (worldObjects[i].GetLoc().y > gfx.GetScreenHeight()) {
			worldObjects[i].GetLoc().y = float(gfx.GetScreenHeight() - 1);
			worldObjects[i].InverseVelY();
		}
	}
	// Merge objects that have collided
	//if (worldObjects.currentAssignedObjects > 1)
	//{
	//	for (int i = 0; i < worldObjects.currentAssignedObjects - 1; i++)
	//	{
	//		for (int j = i + 1; j < worldObjects.currentAssignedObjects; j++)
	//		{
	//			if (CheckCollision(worldObjects, i, j))
	//			{
	//				MergeObjects(&worldObjects, i, j);
	//				j--;
	//				i--;
	//				j--;
	//				break;
	//			}
	//		}
	//	}
	//}
	
}

void Game::ComposeFrame()
{
	//Draw stars
	for (size_t i = 0; i < stars.size(); i++) {
		stars[i].Draw(gfx);
	}
	// Draw objects
	for (int i = 0; i < worldObjects.size(); i++)
	{
		gfx.PutPixel(int(worldObjects[i].GetLoc().x), int(worldObjects[i].GetLoc().y), worldObjects[i].GetColor());
	}
	end = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsedTime = end - start;
	dt = elapsedTime.count();

	start = std::chrono::steady_clock::now(); 


}

