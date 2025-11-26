#include "Button.h"

// must load sprite before initialising
void Button::init(ResourceManager& rm, MyD3D& d3d, Vector2 pos_, float collisionRad) {
	collider.init(rm, d3d, pos_, collisionRad);
}
void Button::update(float dTime, Vector2 mousePos, bool isLMBPressed) {
	if (collider.isColliding(mousePos)) {
		if (!isHovered) 
			triggerBeginHover = true;
		else
			triggerBeginHover = false;
		isHovered = true;
		if (isLMBPressed) {
			if (!isButtonDown)
				triggerClick = true;
			else
				triggerClick = false;
			isButtonDown = true;
		}
		else {
			isButtonDown = false;
		}
	}
	else {
		isButtonDown = false;
		isHovered = false;
		triggerClick = false;
		triggerBeginHover = false;
	}
}
void Button::setPos(Vector2 pos) {
	collider.setPos(pos);
}

// BASIC BUTTON

void BasicBtn::init(MyD3D& d3d, ResourceManager& rm, Vector2 size, string texName, RECT texRect, Vector2 pos_, float rotation_, Vector2 scale_) {
	float texScaleX = size.x / (texRect.right - texRect.left);
	float texScaleY = size.x / (texRect.bottom - texRect.top);
	spr.init(texName, texRect, pos_, rotation_, { texScaleX * scale_.x, texScaleY * scale_.y });
	spr.setOrigin({ 0.5, 0.5 });
	btn.init(rm, d3d, pos_, spr.GetScreenSize().x / 2);
}
void BasicBtn::init(MyD3D& d3d, ResourceManager& rm, ResourceManager::Spritesheet sprSheet, int sprID, Vector2 pos_, float rotation_, Vector2 scale_) {
	spr.init(sprSheet, sprID, pos_, rotation_, scale_);
	spr.setOrigin({ 0.5, 0.5 });
	btn.init(rm, d3d, pos_, spr.GetScreenSize().x / 2);
}
void BasicBtn::initText(string fontName_, string msg_, Vector2 pos_, Vector4 colour_) {
	txt = Text(fontName_, msg_, spr.getPos() + pos_, colour_);
	useTxt = true;
}
void BasicBtn::initText(string fontName_, string msg_) {
	txt = Text(fontName_, msg_);
	useTxt = true;
}
void BasicBtn::update(float dTime, Vector2 mousePos, bool isLMBPressed) {
	btn.update(dTime, mousePos, isLMBPressed);
	if (btn.getTriggerBeginHover())
		spr.setScale({ hoverScale, hoverScale });
	else if (!btn.getIsHovered())
		spr.setScale({ 1, 1 });
}
void BasicBtn::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	spr.render(d3d, rm, dTime, batch);
	if(useTxt)
		txt.render(d3d, rm, dTime, batch);
}
void BasicBtn::setPos(Vector2 pos) {
	btn.setPos(pos);
	spr.setPos(pos);
	if (useTxt)
		txt.setPos(pos);
}
