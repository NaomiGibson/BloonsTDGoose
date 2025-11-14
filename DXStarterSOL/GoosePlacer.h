#pragma once
#include "Sprite.h"
#include "Goose.h"

// appears on clicking place goose button
// follows the mouse and triggers a new gose to spawn wherever the player clicks
class GoosePlacer
{
private:
	bool isActive = false;
	Sprite spr;
public:
	void init(ResourceManager& rm, MyD3D& d3d);
	void update(Vector2 mousePos, bool isLMBPressed, Goose geese[]);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	// spawn goose at pos
	void placeGoose(Vector2 pos, Goose geese[]);
	void activate();
};

