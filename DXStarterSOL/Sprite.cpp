#include "Sprite.h"

void Sprite::init(string texName_, RECT texRect_, Vector2 pos_, float rotation_, Vector2 scale_) {
	texName = texName_;
	texRect = texRect_;
	pos = pos_;
	rotation = rotation_;
	scale = scale_;
}
void Sprite::init(ResourceManager::Spritesheet sprSheet, int sprID, Vector2 pos_, float rotation_, Vector2 scale_) {
	texName = sprSheet.texName;
	texRect = sprSheet.texRects[sprID - 1];
	pos = pos_;
	rotation = rotation_;
	scale = scale_;
}

void Sprite::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	batch.Draw(rm.findTex(texName), pos, &texRect, Vector4(1, 1, 1, 1), rotation, origin, scale, DirectX::SpriteEffects::SpriteEffects_None, 1);
}
string Sprite::getTexName() {
	return texName;
}
void Sprite::setTexName(string texName_) {
	texName = texName_;
}
RECT Sprite::getTexRect() {
	return texRect;
}
void Sprite::setTexRect(RECT texRect_) {
	texRect = texRect_;
}
Vector2 Sprite::getOrigin() {
	return origin;
}
Vector2 Sprite::getPos() {
	return pos;
}
float Sprite::geRotation() {
	return rotation;
}
Vector2 Sprite::getScale() {
	return scale;
}
void Sprite::setScale(const Vector2& scale_) {
	scale = scale_;
}