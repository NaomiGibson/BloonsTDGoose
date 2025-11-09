#pragma once
#include "Sprite.h"

class Collider
{
private:
	Vector2 centre{ 0, 0 };
	float rad{ 10 };
	Sprite db_spr;
public:
	void init(ResourceManager& rm, MyD3D& d3d, Vector2 centre_, float rad_);
	void db_render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	void setPos(Vector2 pos_);
	Vector2 getCentre() { return centre; }
	float getRad() { return rad; }
	void setRad(float rad_);
	float getDistance(const Collider& other);
	bool isColliding(const Collider& other);
	void onCollision(ResourceManager& rm, bool isColliding);
	Sprite& getDbSpr() { return db_spr; }
};