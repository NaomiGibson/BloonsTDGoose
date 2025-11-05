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
	float speed{ 500 };
public:
	Bloon(Track& track_) : track(track_) {};
	Bloon(Track& track_, Vector2 pos_, float speed_) 
		: track(track_) {
		spr.setPos(pos_);
		speed = speed_;
	}
	void init(ResourceManager& rm, MyD3D& d3d);
	// returns false if bloon has reached the end of the track
	bool update(float dTime);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	bool getIsActive() { return isActive; }
	void activate();
	void setSpeed(float speed_) { speed = speed_; }
	void setProgress(float progress_) { progress = progress_; }
};