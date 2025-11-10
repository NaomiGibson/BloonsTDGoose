#pragma once
#include "Sprite.h"
#include "Collider.h"

#include "SimpleMath.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Button
{
private:
	Sprite spr;
	Collider collider;
	bool isButtonDown = false;
public:
	void init(MyD3D& d3d, ResourceManager& rm, Vector2 size, string texName, RECT texRect, Vector2 pos_, float rotation_, Vector2 scale_);
	//void init(ResourceManager::Spritesheet sprSheet, int sprID, Vector2 pos_, float rotation_, Vector2 scale_);
	void update(float dTime, Vector2 mousePos, bool isLMBPressed);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	void onBeginHover();
	void onEndHover();
	void Button::onClick();
	void Button::onUp();
	bool getIsBtnDown() { return isButtonDown; }
};