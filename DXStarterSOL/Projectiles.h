#pragma once
#include "Utils.h"
#include "Sprite.h"
#include "Collider.h"

class Projectiles
{
private:
	Sprite spr;
	Collider collider;
	bool isActive[GC::MAX_PROJECTILES] = { false };
	Vector2 position[GC::MAX_PROJECTILES] = { { 0, 0 } };
	Vector2 direction[GC::MAX_PROJECTILES] = { { 0, 0 } };
	float speed[GC::MAX_PROJECTILES]{ 0 };
public:
	Projectiles(){};
	void init(ResourceManager& rm, MyD3D& d3d);
	void update(float dTime);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	Sprite& getSpr() { return spr; }
	Vector2 getPos(int idx) { return position[idx]; }
	bool getIsActive(int idx) { return isActive[idx]; }
	void activate(Vector2 startPos, float directionRads);
	void setSpeed(float speed_, int idx) { speed[idx] = speed_; }
	Collider& getCollider(int idx);
	void onCollision_bloon(int idx);
};