#pragma once
#include <windows.h>
#include <string>
#include <cassert>
#include <d3d11.h>
#include <iomanip>
#include <vector>

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
#include "Bloons.h"
#include "Stats.h"
#include "Button.h"
#include "Msg_Bloon.h"

class LoseMode
{
private:
	Sprite spr_bg;
	vector<Msg_Bloon> bloons;
	string loseMsg = "YOULOSE!";
	float msgBloonProgress[8]{ 288, 384, 480, 4992, 5064, 5136, 5208, 5280 };

	BasicBtn btn_reset;
	BasicBtn btn_exit;

	Stats ui_stats;
public:
	LoseMode() {};
	void init(ResourceManager& rm, MyD3D& d3d, Track& track);
	void update(float dTime, Vector2 mousePos, bool isLMBPressed);
	void render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime);
};

