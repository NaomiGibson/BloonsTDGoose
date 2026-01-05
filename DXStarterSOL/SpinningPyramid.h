#pragma once
#include "ResourceManager.h"

class SpinningPyramid
{
private:
	string meshName = "default";
	Vector3 pos = { 0, 0, 0.5 };

	Matrix world;
	Matrix view;
	Matrix proj;

public:
	void init(MyD3D& d3d, ResourceManager& rm); // build pyramid
	void render(MyD3D& d3d, ResourceManager& rm); // draw pyramid
};