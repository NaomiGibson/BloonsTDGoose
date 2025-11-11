#pragma once
#include "Sprite.h"

// appears on clicking place goose button
// follows the mouse and triggers a new gose to spawn wherever the player clicks
class GoosePlacer
{
private:
	bool isActive = false;
	Sprite spr;
public:
	void init(ResourceManager& rm, MyD3D& d3d);
	void update(Vector2 mousePos, bool isLMBPressed);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	void placeGoose(Vector2 pos);
	void setIsActive(bool isActive_) { isActive = isActive_; }
};

