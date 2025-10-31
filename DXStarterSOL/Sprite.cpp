#include "Sprite.h"

Sprite::Sprite(MyD3D& d3d, ResourceManager& rm, wstring texFile, string texName_, RECT texRect_, Vector2 pos_, float rotation_, Vector2 scale_) {
	//Sprite::Sprite(Vector2 pos_, float rotation_, Vector2 scale_) {
	//	//assert(rm.findRect(texName, sprID));
	//	texName = texName_;
	//	texRect = rm.findRect(texName, sprID);
	//	pos = pos_;
	//	rotation = rotation_;
	//	scale = scale_;
	//}
}
void Sprite::init(MyD3D& d3d, ResourceManager& rm, wstring texFile, string texName_, RECT texRect_) {
	rm.loadTexture(d3d, texFile, texName_);
	texName = texName_;
	texRect = texRect_;
	//pos = pos_;
	//rotation = rotation_;
	//scale = scale_;
}
void Sprite::init(MyD3D& d3d, ResourceManager& rm, wstring texFile, string texName_, int rows, int columns, int numSprites) {
	rm.loadSpritesheet(d3d, texFile, texName_, rows, columns, numSprites);
	//texName = texName_;
	//texRect = texRect_;
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