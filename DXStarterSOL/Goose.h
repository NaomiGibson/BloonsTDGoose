#pragma once
#include "Sprite.h"
#include "Bloons.h"
#include "Projectiles.h"
#include "Collider.h"

class Goose
{
private:
	Sprite spr;
	bool isActive{ false };
	float shootSpeed{ 1 }; // minimum time between shots fired
	float range{ 0 };
	float lastShot{ -shootSpeed };
	int bulletDurability{ 1 };
	Collider coll_range; // collider for the shoot range
public:
	void setRange(float rad);
	void init(ResourceManager& rm, MyD3D& d3d);
	void update(float dTime, Bloons& bloons, Projectiles& projectiles);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	Sprite& getSpr() { return spr; }
	Collider& getRangeCollider() { return coll_range; }
	void fire(Bloons& bloons, int idx, Projectiles& projectiles);
	bool findTarget(Bloons& bloons, Projectiles& projectiles);
	void activate(Vector2 pos);
};