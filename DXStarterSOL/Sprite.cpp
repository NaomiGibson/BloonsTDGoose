#include "Sprite.h"

void Sprite::init(string texName_, RECT texRect_, Vector2 pos_, float rotation_, Vector2 scale_) {
	texName = texName_;
	texRect = texRect_;
	pos = pos_;
	setRotation(rotation_);
	scale = scale_;
}
void Sprite::init(ResourceManager::Spritesheet& sprSheet, int sprID, Vector2 pos_, float rotation_, Vector2 scale_) {
	texName = sprSheet.texName;
	texRect = sprSheet.texRects[sprID - 1];
	pos = pos_;
	setRotation(rotation_);
	scale = scale_;
}

void Sprite::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	if(isActive)
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

void Sprite::setOrigin(Vector2 origin_) {
	origin = {	(texRect.right - texRect.left) * origin_.x,
				(texRect.bottom - texRect.top) * origin_.y
			};
}
Vector2 Sprite::getPos() {
	return pos;
}
void Sprite::setPos(Vector2 pos_) {
	pos = pos_;
}
float Sprite::getRotation() {
	return rotation;
}
void Sprite::setRotation(float rotation_) {
	if (rotation_ > 360)
		rotation = rotation - 360;
	else
		rotation = rotation_ * 0.01745329251f;
}
void Sprite::setRotationRads(float rads) {
	rotation = rads;
}
Vector2 Sprite::getScale() {
	return scale;
}
void Sprite::setScale(const Vector2& scale_) {
	scale = scale_;
}
Vector2 Sprite::GetScreenSize() {
	return { (texRect.right - texRect.left) * scale.x, (texRect.bottom - texRect.top) * scale.y };
}
Vector2 Sprite::getTexSize() {
	return { (float)texRect.right - (float)texRect.left, (float)texRect.bottom - (float)texRect.top };
}
bool Sprite::getIsActive() {
	return isActive;
}
void Sprite::setIsActive(bool isActive_) {
	isActive = isActive_;
}

// SPRITE ANIMATION

void SpriteAnimation::update(ResourceManager& rm, float dTime) {
	if (mSpr.getIsActive()) {
		if (!mPlay)
			return;
		mElapsedSec += dTime;
		if (mElapsedSec > (1.f / mRateSec)) {
			mElapsedSec = 0;
			mCurrent++;
			if (mCurrent > mStop) {
				mCurrent = mStart;
				if (!mLoop)
					mPlay = false;
			}
			mSpr.setTexRect(rm.findRect(mSpr.getTexName(), mCurrent)); // set sprite texture rect to current frame
		}
	}
}
