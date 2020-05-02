#pragma once
#include "Graphics.h"
#include "Vec2.h"
#define M_PI 3.14159f
#define M_PI_4 0.78539f
#define M_PI_2  1.57079f
class Star {
public:
	void Init(Vec2 in_pos, float in_size, float in_st, float in_RotAng, float in_RotSpd, Color in_col);
	void Draw(float Size, float theta, Vec2 position, Graphics& gfx) const;
	void Draw(Graphics& gfx) const;
	void Update(const Graphics& gfx);
	Vec2 GetPos() const;
	float GetSize() const;
	float GetMovingAngle() const;
	float GetRotAngle() const;
	float GetRotSpd() const;
	Color GetCol() const;

private:
	Color col;
	Vec2 pos;
	float size;
	float st; //star moving angle
	float RotAng, RotSpd; //rotation angle, speed
	bool ClonedOnce;
};
