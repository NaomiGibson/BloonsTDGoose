#include "Button.h"

// must load sprite before initialising
void Button::init(MyD3D& d3d, ResourceManager& rm, Vector2 size, string texName, RECT texRect, Vector2 pos_, float rotation_, Vector2 scale_) {
	float texScaleX = size.x / (texRect.right - texRect.left);
	float texScaleY = size.x / (texRect.bottom - texRect.top);
	spr.init(texName, texRect, pos_, rotation_, { texScaleX * scale_.x, texScaleY * scale_.y });
	spr.setOrigin({ 0.5, 0.5 });
	collider.init(rm, d3d, pos_, (texRect.right - texRect.left * texScaleX) / 2);
}
void Button::init(MyD3D& d3d, ResourceManager& rm, ResourceManager::Spritesheet sprSheet, int sprID, Vector2 pos_, float rotation_, Vector2 scale_) {
	spr.init(sprSheet, sprID, pos_, rotation_, scale_);
	spr.setOrigin({ 0.5, 0.5 });
	collider.init(rm, d3d, pos_, (sprSheet.texRects[sprID].right - sprSheet.texRects[sprID].left * scale_.x) / 2);
}
void Button::update(float dTime, Vector2 mousePos, bool isLMBPressed) {
	if (collider.isColliding(mousePos)) {
		onBeginHover();
		if (isLMBPressed)
			onClick();
		else
			onUp();
	}
	else
		onEndHover();
}
void Button::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	spr.render(d3d, rm, dTime, batch);
}
void Button::onBeginHover() {
	spr.setScale({ hoverScale, hoverScale });

}
void Button::onEndHover() {
	spr.setScale({ 1, 1 });
}
void Button::onClick() {
	isButtonDown = true;
}
void Button::onUp() {
	isButtonDown = false;
}

void BtnWithTxt::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	Button::render(d3d, rm, dTime, batch);
	txt.render(d3d, rm, dTime, batch);
}
void BtnWithTxt::onBeginHover() {
	Button::onBeginHover();
	txt.setScale(hoverScale);
}
void BtnWithTxt::onEndHover() {
	Button::onEndHover();
	txt.setScale(1);
}
void BtnWithTxt::initText(string fontName_, string msg_, Vector2 pos_, Vector4 colour_) {
	txt = Text(fontName_, msg_, spr.getPos() + pos_, colour_);
}
void BtnWithTxt::initText(string fontName_, string msg_) {
	txt = Text(fontName_, msg_);
}