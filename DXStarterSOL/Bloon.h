#pragma once
#include "Sprite.h";
#include "Track.h";

class Bloon
{
private:
	Sprite spr;
	Track& track;
	bool isActive = false;
	float progress{ 0 };
	float speed{ 200 };
public:
	Bloon(Track& track_) : track(track_) {};
	void init(ResourceManager& rm, MyD3D& d3d);
	// returns false if bloon has reached the end of the track
	bool update(float dTime);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
};