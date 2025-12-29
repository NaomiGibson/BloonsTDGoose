#pragma once
#include "ResourceManager.h"

class SpinningPyramid
{
private:
	string meshName = "default";
	Vector3 pos;
	Vector3 vel;
public:
	void init(MyD3D& d3d, ResourceManager& rm); // build cube
	void update(MyD3D& d3d, ResourceManager& rm); // calculate verts based on rotation
	void render(MyD3D& d3d, ResourceManager& rm); // draw pyramid
};

