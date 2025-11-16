#pragma once
#include "Sprite.h"
#include "Projectiles.h"
#include "Collider.h"
#include "Track.h"
//#include "Utils.h"

class Bloons 
{
private:
	// Shared bloon data
	Sprite spr;
	Track& track;
	Collider collider;

	// individual bloon data. Access a particular bloon using its index
	int layer[GC::MAX_BLOONS] = { 0 };					// used to spawn some bloons underneath bridges and some over
	bool isActive[GC::MAX_BLOONS] = { false };
	int value[GC::MAX_BLOONS] = { 1 };					// how many coins popping bloons reward
	float progress[GC::MAX_BLOONS] = { 100 };			// how far along the track bloons are
	Vector2 position[GC::MAX_BLOONS] = { { 0, 0 } };
	float speed[GC::MAX_BLOONS] = { 0 };

	// ROUNDS AND WAVES
	int bloonsSpawned = 0; // number of bloons spawned from the current wave
	struct Wave {
		int numBloons;				// total number of bloons to spawn
		float spawnRate;			// time between spawning bloons
		vector<int> bloonHealth;	// health of bloons spawned rotates through the given values
		float wait;					// recovery time between this wave and the next
		Wave(int numBloons_, float spawnRate_, vector<int> bloonHealth_, float wait_)
			: numBloons(numBloons_), spawnRate(spawnRate_),  bloonHealth(bloonHealth_), wait(wait_) 
		{};
	};
	typedef vector<Wave> round; // a round is a collection of waves
	int currRound{ 0 };
	int currWave{ 0 };

	// ~~~ DEFINE ROUNDS HERE ~~~
	round rounds[2]{ 
		{ // round 1
			{ 5, 2, { 1 }, 3 },
			{ 10, 0.5, { 1 }, 3 } 
		},
		{ // round 2
			{ 2, 0.1, { 1 }, 3 } 
		}
	};
public:
	Bloons(Track& track_) : track(track_) {};
	void init(ResourceManager& rm, MyD3D& d3d);
	void endWave();
	void endRound();
	// Handles all bloon spawning logic
	// @param idx must be that of an inactive bloon
	void spawnBloon(int idx);
	// @return true if one or more bloons have reached the end of the track
	bool update(float dTime);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch, int layer_);
	void reset();
	Sprite& getSpr() { return spr; }
	bool getIsActive(int idx) { return isActive[idx]; }
	int getNumActiveBloons();
	bool isRoundFinished();
	bool areAllRoundsFinished();
	int getBloonsSpawned() { return bloonsSpawned; }
	Vector2 getPos(int idx) { return position[idx]; }
	void activate(int idx);
	void setSpeed(float speed_, int idx) { speed[idx] = speed_; }
	void setProgress(float progress_, int idx) { progress[idx] = progress_; }
	Collider& getCollider(int idx);
	void onCollision_projectile(int idx);
};