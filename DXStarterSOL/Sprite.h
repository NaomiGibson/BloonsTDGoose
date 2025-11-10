#pragma once
#include <windows.h>
#include <string>
#include <cassert>
#include <d3d11.h>
#include <iomanip>
#include <vector>

#include "SimpleMath.h"
#include "SpriteFont.h"
#include "DDSTextureLoader.h"
#include "CommonStates.h"
#include "ResourceManager.h"
#include "Utils.cpp"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Sprite
{
public:
	Sprite::Sprite() {};
	void init(string texName_, RECT texRect_, Vector2 pos_, float rotation_, Vector2 scale_); // initialise sprite with a whole texture
	void init(ResourceManager::Spritesheet sprSheet, int sprID, Vector2 pos_, float rotation_, Vector2 scale_); // initialise sprite with spritesheet
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	string getTexName();
	void setTexName(string texName);
	RECT getTexRect();
	void setTexRect(RECT texRect_);
	Vector2 getOrigin();
	void setOrigin(Vector2 origin_);
	Vector2 getPos();
	void setPos(Vector2 pos_);
	float getRotation();
	void setRotation(float rotation_);
	void Sprite::setRotationRads(float rads);
	Vector2 getScale();
	void setScale(const Vector2& scale_);
	Vector2 GetScreenSize();

protected:
	string texName{ "default" };
	RECT texRect{ 0, 0, 0, 0 };
	Vector2 origin{ 0, 0 };
	Vector2 pos{ 0, 0 };
	float rotation{ 0 };
	Vector2 scale{ 1, 1 };
};
