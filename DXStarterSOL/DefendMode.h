#pragma once
#include <windows.h>
#include <string>
#include <cassert>
#include <d3d11.h>
#include <iomanip>

#include "WindowUtils.h"
#include "D3DUtil.h"
#include "D3D.h"
#include "SimpleMath.h"
#include "SpriteFont.h"
using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

//#include "Utils.h"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Goose.h"
#include "Bloons.h"
#include "Projectiles.h"
#include "Stats.h"
#include "Button.h"

class DefendMode
{
private:
	Stats ui_stats;
	Projectiles projectiles{};
	BasicBtn btn_gameSpeed;
	Sprite spr_bg;
	Sprite spr_bridge1;
	Sprite spr_bridge2;
	const float FAST_TIME_SCALE{ 3 };
	bool isGameFast{ false };
	bool isGameSpeedBtnDown{ false };
public:
	DefendMode() {};
	void init(ResourceManager& rm, MyD3D& d3d, Goose geese[], Bloons& bloons);
	void handleCollision(ResourceManager& rm, Bloons& bloons);
	void update(ResourceManager& rm, float dTime, Vector2 mousePos, bool isLMBPressed, bool keyboard[], Goose geese[], Bloons& bloons);
	void render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime, Goose geese[], Bloons& bloons);
	void reset(Bloons& bloons);
	void toggleTimeScale();
};

