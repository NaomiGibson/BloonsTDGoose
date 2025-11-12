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

#include "Utils.cpp"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Goose.h"
#include "Bloons.h"
#include "Projectiles.h"
#include "Stats.h"

class DefendMode
{
private:
	Sprite spr_test;
	Sprite spr_bg;
	Sprite spr_bridge1;
	Sprite spr_bridge2;
	Goose goose;
	Goose goose2;
	Goose goose3;
	Projectiles projectiles{};
	Bloons bloons{ track };
	Track track{ {
		{-48, 360},
		{528, 360},
		{528, 648},
		{240, 648},
		{240, 68},
		{1392, 68},
		{1392, 452},
		{1296, 452},
		{1296, 1032},
		{720, 1032},
		{720, 552},
		{1008, 552},
		{1008, 840},
		//{528, 840},
		{-48, 840},
		} };
	Stats ui_stats;
public:
	DefendMode() {};
	void init(ResourceManager& rm, MyD3D& d3d);
	void handleCollision(ResourceManager& rm);
	Modes update(ResourceManager& rm, float dTime, float timeScale);
	void render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime);
	void reset();
};

