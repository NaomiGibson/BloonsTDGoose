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

// track for an object to move along.
// supports straight vertical and horizontal lines and 90 degree turns
class Track
{
private:
	vector<Vector2> points;
	float length{ 0 };
public:
	Track(vector<Vector2> points_) { points = points_; };
	void init() { length = calculateLength(); }
	// find location at n distance along track
	Vector2 findPos(float progress);
	// calculate length between 2 points
	float getLength(Vector2 wp1, Vector2 wp2);
	// return length of entire track
	float calculateLength();
	float getLength() { return length; }
};