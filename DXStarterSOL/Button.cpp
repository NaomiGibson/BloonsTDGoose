#include "Button.h"

// must load sprite before initialising
void Button::init(MyD3D& d3d, ResourceManager& rm, Vector2 size, string texName, RECT texRect, Vector2 pos_, float rotation_, Vector2 scale_) {
	float texScaleX = size.x / (texRect.right - texRect.left);
	float texScaleY = size.x / (texRect.bottom - texRect.top);
	spr.init(texName, texRect, pos_, rotation_, { texScaleX * scale_.x, texScaleY * scale_.y });
	spr.setOrigin({ 0.5, 0.5 });
	collider.init(rm, d3d, pos_, (texRect.right - texRect.left * texScaleX) / 2);
}
//void Button::init(ResourceManager::Spritesheet sprSheet, int sprID, Vector2 pos_, float rotation_, Vector2 scale_) {
//}
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
	spr.setScale({ 1.1f, 1.1f });

}
void Button::onEndHover() {
	spr.setScale({ 1.f, 1.f });
}
void Button::onClick() {
	isButtonDown = true;
}
void Button::onUp() {
	isButtonDown = false;
}