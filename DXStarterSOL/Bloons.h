#pragma once
#include "Sprite.h";
#include "Track.h";
#include "Utils.cpp"

class Bloons 
{
private:
	Sprite spr;
	Track& track;
	bool isActive[GC::MAX_BLOONS] = { false };
	float progress[GC::MAX_BLOONS] = { 100 };
	float speed[GC::MAX_BLOONS] = { 0 };
public:
	Bloons(Track& track_) : track(track_) {};
	void init(ResourceManager& rm, MyD3D& d3d);
	// Handles all bloon spawning logic
	// @return true if a bloon spawned
	void spawnBloon(int idx);
	// returns false if one or more bloons have reached the end of the track
	bool update(float dTime);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	Sprite& getSpr() { return spr; }
	bool getIsActive(int idx) { return isActive; }
	void activate(int idx);
	void setSpeed(float speed_, int idx) { speed[idx] = speed_; }
	void setProgress(float progress_, int idx) { progress[idx] = progress_; }

};