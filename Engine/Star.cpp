#include "Star.h"


void Star::Init(Vec2 in_pos, float in_size, float in_st, float in_RotAng, float in_RotSpd, Color in_col)
{
	pos = in_pos;
	size = in_size;
	st = in_st;
	RotAng = in_RotAng;
	RotSpd = in_RotSpd;
	col = in_col;
}

void Star::Draw(float Size, float theta, Vec2 position, Graphics& gfx) const
{
	float cosVal = cos(theta);
	float sinVal = sin(theta);
	int x1 = 0;
	int y2 = 0;

	int y1 = -int(Size * 0.92f);
	for (int x2 = 0; x2 < Size; x2 = x2 + 10)
	{
		int rotx1 = int(x1 * cosVal - y1 * sinVal);
		int roty1 = int(x1 * sinVal + y1 * cosVal);
		int rotx2 = int(x2 * cosVal - y2 * sinVal);
		int roty2 = int(x2 * sinVal + y2 * cosVal);
		gfx.DrawLine(rotx1 + int(position.x), roty1 + int(position.y), rotx2 + int(position.x), roty2 + int(position.y), col);
		if (y1 < 0) y1 = y1 + 10;
	}
	// Hieght
	y1 = int(Size);
	//across
	for (int x2 = 0; x2 < int(Size); x2 = x2 + 10)
	{
		int rotx1 =int(x1 * cosVal - y1 * sinVal);
		int roty1 =int(x1 * sinVal + y1 * cosVal);
		int rotx2 =int( x2 * cosVal - y2 * sinVal);
		int roty2 =int(x2 * sinVal + y2 * cosVal);
		gfx.DrawLine(rotx1 +int(position.x), roty1 +int(position.y), rotx2 +int(position.x), roty2 +int(position.y), col);
		if (y1 > 0) y1 = y1 - 10;
	}
	y1 = int(Size);
	//across
	for (int x2 = 0; x2 > -int(Size); x2 = x2 - 10)
	{
		int rotx1 =int(x1 * cosVal - y1 * sinVal);
		int roty1 =int(x1 * sinVal + y1 * cosVal);
		int rotx2 =int( x2 * cosVal - y2 * sinVal);
		int roty2 =int(x2 * sinVal + y2 * cosVal);
		gfx.DrawLine(rotx1 +int(position.x), roty1 +int(position.y), rotx2 +int(position.x), roty2 +int(position.y), col);
		if (y1 > 0) y1 = y1 - 10;
	}
	y1 = -int(Size * 0.92f);
	for (int x2 = 0; x2 > -int(Size); x2 = x2 - 10)
	{
		int rotx1 =int(x1 * cosVal - y1 * sinVal);
		int roty1 =int(x1 * sinVal + y1 * cosVal);
		int rotx2 =int( x2 * cosVal - y2 * sinVal);
		int roty2 =int(x2 * sinVal + y2 * cosVal);
		gfx.DrawLine(rotx1 +int(position.x), roty1 +int(position.y), rotx2 +int(position.x), roty2 +int(position.y), col);
		if (y1 < 0) y1 = y1 + 10;
	}
}

void Star::Draw(Graphics & gfx) const
{
	float cosVal = cos(RotAng);
	float sinVal = sin(RotAng);
	int x1 = 0;
	int y2 = 0;

	int y1 = -int(size * 0.92);
	for (int x2 = 0; x2 < int(size); x2 = x2 + 10)
	{
		int rotx1 =int(x1 * cosVal - y1 * sinVal);
		int roty1 =int(x1 * sinVal + y1 * cosVal);
		int rotx2 =int( x2 * cosVal - y2 * sinVal);
		int roty2 =int(x2 * sinVal + y2 * cosVal);
		gfx.DrawLine(rotx1 + int(pos.x), roty1 + int(pos.y), rotx2 + int(pos.x), roty2 + int(pos.y), col);
		if (y1 < 0) y1 = y1 + 10;
	}
	// Hieght
	y1 = int(size);
	//across
	for (int x2 = 0; x2 < int(size); x2 = x2 + 10)
	{
		int rotx1 =int(x1 * cosVal - y1 * sinVal);
		int roty1 =int(x1 * sinVal + y1 * cosVal);
		int rotx2 =int( x2 * cosVal - y2 * sinVal);
		int roty2 =int(x2 * sinVal + y2 * cosVal);
		gfx.DrawLine(rotx1 + int(pos.x), roty1 + int(pos.y), rotx2 + int(pos.x), roty2 + int(pos.y), col);
		if (y1 > 0) y1 = y1 - 10;
	}
	y1 = int(size);
	//across
	for (int x2 = 0; x2 > -int(size); x2 = x2 - 10)
	{
		int rotx1 =int(x1 * cosVal - y1 * sinVal);
		int roty1 =int(x1 * sinVal + y1 * cosVal);
		int rotx2 =int( x2 * cosVal - y2 * sinVal);
		int roty2 =int(x2 * sinVal + y2 * cosVal);
		gfx.DrawLine(rotx1 + int(pos.x), roty1 + int(pos.y), rotx2 + int(pos.x), roty2 + int(pos.y), col);
		if (y1 > 0) y1 = y1 - 10;
	}
	y1 = -int(size * 0.92f);
	for (int x2 = 0; x2 > -int(size); x2 = x2 - 10)
	{
		int rotx1 =int(x1 * cosVal - y1 * sinVal);
		int roty1 =int(x1 * sinVal + y1 * cosVal);
		int rotx2 =int( x2 * cosVal - y2 * sinVal);
		int roty2 =int(x2 * sinVal + y2 * cosVal);
		gfx.DrawLine(rotx1 + int(pos.x), roty1 + int(pos.y), rotx2 + int(pos.x), roty2 + int(pos.y), col);
		if (y1 < 0) y1 = y1 + 10;
	}
}

void Star::Update(const Graphics& gfx)
{
	pos.x = (pos.x + (RotSpd * 50) * cos(st));
	pos.y = (pos.y + (RotSpd * 50) * sin(st));

	float x0 = sqrt((float)((pos.x)*(pos.x))); // x distance from 0
	float xM = sqrt((float)((pos.x - gfx.GetScreenWidth())*(pos.x - gfx.GetScreenWidth()))); // x distance from window width

	float y0 = sqrt((float)((pos.y)*(pos.y))); // y distance from 0
	float yM = sqrt((float)((pos.y - gfx.GetScreenHeight())*(pos.y - gfx.GetScreenHeight()))); // y distance from window height

	if (x0 < size * 0.7 || xM < size * 0.7 || y0 < size * 0.7 || yM < size * 0.7)//wall colision detection
	{
		st = st + M_PI_2;
	}
	RotAng += RotSpd;
	if (RotAng > M_PI * 2.0)
	{
		RotAng -= M_PI * 2.0;
	}
}

Vec2 Star::GetPos() const
{
	return pos;
}

float Star::GetSize() const
{
	return size;
}

float Star::GetMovingAngle() const
{
	return st;
}

float Star::GetRotAngle() const
{
	return RotAng;
}

float Star::GetRotSpd() const
{
	return RotSpd;
}

Color Star::GetCol() const
{
	return col;
}
