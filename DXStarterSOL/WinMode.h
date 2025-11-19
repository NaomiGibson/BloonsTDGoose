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
#include "Bloons.h"
#include "Stats.h"
#include "Button.h"

class WinMode
{
private:
	//vector<Sprite> spr_bloons;
	//vector<Text> txt_loseMsgs;
	Text txt_winMsg;
	Sprite spr_bg;

	BasicBtn btn_reset;
	//Text txt_reset;
	BasicBtn btn_exit;

	Stats ui_stats;
public:
	WinMode() {};
	void init(ResourceManager& rm, MyD3D& d3d);
	Modes update(float dTime, Vector2 mousePos, bool isLMBPressed);
	void render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime);
};