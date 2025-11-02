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
	string fontName;
	string msg;
	Vector2 pos;
	Vector4 colour;
public:
	Text(string fontName_, string msg_, Vector2 pos_, Vector4 colour_)
		: fontName(fontName_), msg(msg_), pos(pos_), colour(colour_) {};
	string getFontName() { return fontName; }
	void setFontName(string fontName_) { fontName = fontName_; }
	string getMsg() { return msg; }
	void setMsg(string msg_) { msg = msg_; }
	Vector2 getPos() { return pos; }
	void setPos(Vector2 pos_) { pos = pos_; }
	Vector4 getColour() { return colour; }
	void setColour(Vector4 colour_) { colour = colour_; }
	//void init();
	//void update();
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
};