#pragma once
#include <windows.h>
#include <cassert>
#include <vector>
#include <d3d11.h>

#include "D3DUtil.h"
#include "WindowUtils.h"
#include "D3D.h"
#include "SimpleMath.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

#include "Sprite.h"

// track for an object to move along.
// supports straight vertical and horizontal lines and 90 degree turns
class Track
{
private:
	vector<Vector2> points;
	float length{ 0 };
	float width{ 0 };
	Sprite db_spr;

public:
	Track(float width_, vector<Vector2> points_) { 
		width = width_, points = points_; 
		for (unsigned int i(1); i < points.size(); i++) {
			assert(points[i].x == points[i - 1].x || points[i].y == points[i - 1].y); // track only supports 90 degree turns
		}
	};
	void init(ResourceManager& rm, MyD3D& d3d);
	void db_render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	// find location at n distance along track
	Vector2 findPos(float progress);
	Vector2 getPoint(int point) { return points[point - 1]; }
	float getProgressAtPoint(int point);
	// calculate length between 2 points
	float getLength(Vector2 wp1, Vector2 wp2);
	// return length of entire track
	float calculateLength();
	float getLength() { return length; }
	// @return true if the given circle is overlapping the given section 
	// circle is treated like a square the size of the circle
	// (the line between points[section] and points[section + 1] including width)
	bool Track::isOverlappingSection(Vector2 otherCentre, float otherRad);
	// @return true if the given point is overlapping the track
	bool Track::isOverlapping(Vector2 pos, float rad);
};