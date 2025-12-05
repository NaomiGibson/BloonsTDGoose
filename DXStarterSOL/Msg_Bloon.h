#pragma once
#include "Sprite.h"
#include "Text.h"
#include "Track.h"

class Msg_Bloon
{
private:
	Sprite spr;	// bloon sprite
	Text txt{ "Moghul", "x", {0, 0}, {0, 0, 0, 1} };	// letter text
	Vector2 pos;
	float speed{ 3 };
	float hoverHeight{ 4 }; // difference between top of hover position and bottom of hover position
	float hoverOffset{}; // current place in hover
public:
	void init(ResourceManager& rm, MyD3D& d3d, Track& track, float progress, string letter, int health);
	void update(float dTime);
	void render(ResourceManager& rm, MyD3D& d3d, float dTime, SpriteBatch& batch);
};