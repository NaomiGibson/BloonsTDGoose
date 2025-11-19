#pragma once
#include "Sprite.h"
#include "Collider.h"
#include "Text.h"

#include "SimpleMath.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Button
{
protected:
	Collider collider;
	bool isButtonDown = false; // true if the button is being pressed currently
	bool isHovered = false; // true if the mouse is overlapping button
	bool triggerClick = false; // true for 1 frame after button is clicked
	bool triggerBeginHover = false; // true for 1 frame after button is hovered
public:
	void init(ResourceManager& rm, MyD3D& d3d, Vector2 pos_, float collisionRad);
	void update(float dTime, Vector2 mousePos, bool isLMBPressed);
	bool getIsBtnDown() { return isButtonDown; }
	bool getIsHovered() { return isHovered; }
	bool getTriggerClick() { return triggerClick; }
	bool getTriggerBeginHover() { return triggerBeginHover; }
	void setPos(Vector2 pos);
};


class BasicBtn
{
private:
	Button btn;
	Sprite spr;
	Text txt;
	float hoverScale = 1.1;
	bool useTxt = false;
public:
	void init(MyD3D& d3d, ResourceManager& rm, Vector2 size, string texName, RECT texRect, Vector2 pos_, float rotation_, Vector2 scale_);
	void init(MyD3D& d3d, ResourceManager& rm, ResourceManager::Spritesheet sprSheet, int sprID, Vector2 pos_, float rotation_, Vector2 scale_);
	void initText(string fontName_, string msg_, Vector2 pos_, Vector4 colour_);
	void initText(string fontName_, string msg_);
	void update(float dTime, Vector2 mousePos, bool isLMBPressed);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	void setPos(Vector2 pos);
	Sprite& getSpr() { return spr; }
	Button& getButton() { return btn; }
};