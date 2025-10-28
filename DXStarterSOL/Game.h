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

#include "ResourceManager.h"
#include "Sprite.h"

class Game
{
private:
	MyD3D* p_d3d;
	ResourceManager rm; // game's resource manager

	DirectX::SpriteBatch* gpSpriteBatch = nullptr;
	Sprite spr_bg{ *p_d3d, rm, L"../bin/data/BloonsMap.dds", "main_background", { 0, 0, 1920, 1080 }, {0, 0}, 0 };

	int gCycle = 0;
	float gTime = 0;
	float gResTimer = 0;
	int gFrameCounter = 0;
	float gFrameTimer = 0;
public:
	Game(MyD3D*);
	void init();
	void release();
	void update();
	void render();
};