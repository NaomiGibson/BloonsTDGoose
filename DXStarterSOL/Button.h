#pragma once
#include "Sprite.h"
#include "Collider.h"
#include "Text.h"

#include "SimpleMath.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Button
{
protected:
	Sprite spr;
	Collider collider;
	bool isButtonDown = false;
	float focusedScale = 1.1f;
	void (*fp_onBeginHover)(Button&) = &focusScale;
	void (*fp_onEndHover)(Button&) = &unfocusScale;
	void (*fp_onDown)(Button&) = nullptr;
	void (*fp_onUp)(Button&) = nullptr;
	//void (*fp_onClick)();
	//void (*fp_onRelease)();
public:
	Button(void(*fp_onBeginHover_)(Button&), void(*fp_onEndHover_)(Button&), void (*fp_onDown_)(Button&), void (*fp_onUp_)(Button&))
		: fp_onBeginHover(fp_onBeginHover_), fp_onEndHover(fp_onEndHover_), fp_onDown(fp_onDown_), fp_onUp(fp_onUp_)
	{}
	Button(void (*fp_onDown_)(Button&), void (*fp_onUp_)(Button&))
		: fp_onDown(fp_onDown_), fp_onUp(fp_onUp_)
	{}
	Button(void (*fp_onDown_)(Button&))
		: fp_onDown(fp_onDown_)
	{}

	void init(MyD3D& d3d, ResourceManager& rm, Vector2 size, string texName, RECT texRect, Vector2 pos_, float rotation_, Vector2 scale_);
	void init(MyD3D& d3d, ResourceManager& rm, ResourceManager::Spritesheet sprSheet, int sprID, Vector2 pos_, float rotation_, Vector2 scale_);
	void update(float dTime, Vector2 mousePos, bool isLMBPressed);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	bool getIsBtnDown() { return isButtonDown; }
	Sprite& getSpr() { return spr; }
	static void focusScale(Button& btn) { btn.getSpr().setScale({ btn.focusedScale, btn.focusedScale }); };
	static void unfocusScale(Button& btn) { btn.getSpr().setScale({ 1, 1 }); };
};


class BtnWithTxt : public Button
{
private:
	Text txt;
public:
	//BtnWithTxt(void(*fp_onBeginHover_)(Button&), void(*fp_onEndHover_)(Button&), void (*fp_onDown_)(Button&), void (*fp_onUp_)(Button&))
	//	: fp_onBeginHover(fp_onBeginHover_), fp_onEndHover(fp_onEndHover_), fp_onDown(fp_onDown_), fp_onUp(fp_onUp_)
	//{}
	//BtnWithTxt(void (*fp_onDown_)(Button&), void (*fp_onUp_)(Button&))
	//	: fp_onDown(fp_onDown_), fp_onUp(fp_onUp_)
	//{}
	//BtnWithTxt(void (*fp_onDown_)(Button&))
	//	: fp_onDown(fp_onDown_)
	//{}
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	void initText(string fontName_, string msg_, Vector2 pos_, Vector4 colour_);
	void initText(string fontName_, string msg_);
};