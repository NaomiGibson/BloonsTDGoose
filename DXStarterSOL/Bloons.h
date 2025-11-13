#pragma once
#include "Sprite.h"
#include "Projectiles.h"
#include "Collider.h"
#include "Track.h"
//#include "Utils.h"

class Bloons 
{
private:
	Sprite spr;
	Track& track;
	Collider collider;
	int layer[GC::MAX_BLOONS] = { 0 };
	bool isActive[GC::MAX_BLOONS] = { false };
	int value[GC::MAX_BLOONS] = { 1 };
	float progress[GC::MAX_BLOONS] = { 100 };
	Vector2 position[GC::MAX_BLOONS] = { { 0, 0 } };
	float speed[GC::MAX_BLOONS] = { 0 };
	int bloonsSpawned = 0;
public:
	Bloons(Track& track_) : track(track_) {};
	void init(ResourceManager& rm, MyD3D& d3d);
	// Handles all bloon spawning logic
	// @return true if a bloon spawned
	void spawnBloon(float timeScale, int idx);
	// @return true if one or more bloons have reached the end of the track
	bool update(float dTime, float timeScale);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch, int layer_);
	void reset();
	Sprite& getSpr() { return spr; }
	bool getIsActive(int idx) { return isActive[idx]; }
	int getNumActiveBloons();
	int getBloonsSpawned() { return bloonsSpawned; }
	Vector2 getPos(int idx) { return position[idx]; }
	void activate(int idx);
	void setSpeed(float speed_, int idx) { speed[idx] = speed_; }
	void setProgress(float progress_, int idx) { progress[idx] = progress_; }
	Collider& getCollider(int idx);
	void onCollision_projectile(int idx);
};