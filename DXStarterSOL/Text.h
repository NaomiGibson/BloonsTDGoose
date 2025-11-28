#pragma once
#include <windows.h>
#include <string>
#include <cassert>

#include "SimpleMath.h"
#include "SpriteFont.h"
#include "ResourceManager.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Text
{
private:
	string fontName{ "default" };
	string msg{ "msg" };
	Vector2 pos{ 0, 0 };
	float rotation{ 0 };
	Vector2 origin{ 0, 0 };
	Vector4 colour{ 0, 0, 0, 1 };
	float scale{ 1 };
public:
	Text() {};
	Text(string fontName_, string msg_, Vector2 pos_, Vector4 colour_)
		: fontName(fontName_), msg(msg_), pos(pos_), colour(colour_) {};

	Text(string fontName_, string msg_)
		: fontName(fontName_), msg(msg_) {
		pos = { 0, 0 }, colour = { 0, 0, 0, 1 };
	};
	string getFontName() { return fontName; }
	void setFontName(string fontName_) { fontName = fontName_; }
	string getMsg() { return msg; }
	void setMsg(string msg_) { msg = msg_; }
	Vector2 getPos() { return pos; }
	void setPos(Vector2 pos_) { pos = pos_; }
	Vector2 getOrigin() { return origin; }
	void setOrigin(Vector2 origin_) { origin = origin_; }
	Vector4 getColour() { return colour; }
	void setColour(Vector4 colour_) { colour = colour_; }
	float getScale() { return scale; }
	void setScale(float scale_) { scale = scale_; }
	//void init();
	//void update();
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
};