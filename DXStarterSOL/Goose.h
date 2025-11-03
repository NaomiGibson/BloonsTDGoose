#pragma once
#include "Sprite.h"
#include "Bloon.h"

class Goose
{
private:
	Sprite spr;
	bool isActive{ false };
	float shootSpeed{ 1 }; // minimum time between shots fired
	float range{ 0 };
	int bulletDurability{ 1 };

	Sprite spr_range;
public:
	void setRange(float rad);
	void init(ResourceManager& rm, MyD3D& d3d);
	void update(float dTime);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	// returns direction in which to shoot (aiming slightly in front of the target bloon)
	Vector2 findTarget(Track& track);
	void shoot();
};