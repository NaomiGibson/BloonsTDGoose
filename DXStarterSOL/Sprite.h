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

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Sprite
{
public:
	Sprite(MyD3D& d3d, ResourceManager& rm, wstring texFile, string texName_, RECT texRect, Vector2 pos_ = Vector2(0, 0), float rotation_ = 0, Vector2 scale_ = Vector2(1, 1));
	Sprite(ResourceManager& rm, string texName_, int sprID, Vector2 pos_, float rotation_, Vector2 scale_);
	Sprite::Sprite() {};
	void Sprite::init(MyD3D& d3d, ResourceManager& rm, wstring texFile, string texName_, RECT texRect_);
	void Sprite::init(MyD3D& d3d, ResourceManager& rm, wstring texFile, string texName_, int rows, int columns, int numSprites);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	string getTexName();
	void setTexName(string texName);
	RECT getTexRect();
	void setTexRect(RECT texRect_);
	Vector2 getOrigin();
	Vector2 getPos();
	float geRotation();
	Vector2 getScale();
	void setScale(const Vector2& scale_); 

protected:
	string texName;
	RECT texRect;
	Vector2 origin{ 0, 0 };
	Vector2 pos;
	float rotation;
	Vector2 scale{ 1, 1 };
};
