#pragma once
#include "Sprite.h"
#include "Bloons.h"
#include "Projectiles.h"
#include "Collider.h"
#include "Button.h"

class Goose
{
private:
	Sprite spr;
	bool isActive{ false };
	float shootSpeed{ 2 }; // minimum time between shots fired
	//float range{ 0 };
	float lastShot{ -shootSpeed };
	int bulletDurability{ 1 };
	Collider coll_range; // collider for the shoot range
	Collider coll_goose; // collider for goose body
	Button btn_selectGoose;
	Sprite spr_rangeIndicator;
public:
	void init(ResourceManager& rm, MyD3D& d3d);
	void updateDefend(float dTime, Bloons& bloons, Projectiles& projectiles, Vector2 mousePos, bool isLMBPressed);
	void updatePlace(float dTime, Vector2 mousePos, bool isLMBPressed);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	void setRange(float rad);
	Sprite& getSpr() { return spr; }
	Collider& getRangeCollider() { return coll_range; }
	Collider& getGooseCollider() { return coll_goose; }
	void fire(Bloons& bloons, int idx, Projectiles& projectiles);
	bool findTarget(Bloons& bloons, Projectiles& projectiles);
	bool getIsActive() { return isActive; }
	void activate(Vector2 pos);
	void deactivate() { isActive = false; }
};