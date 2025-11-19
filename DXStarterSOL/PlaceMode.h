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
#include "Sprite.h"
#include "Goose.h"
#include "Stats.h"
#include "Button.h"
#include "GoosePlacer.h"
#include "UI_GooseUpgrades.h"

class PlaceMode
{
private:
	Sprite spr_bg;
	Stats ui_stats;
	BasicBtn btn_play;
	UI_PurchaseBtn btn_placeGoose;
	UI_GooseUpgrades ui_gooseUpgrades; 
	GoosePlacer ui_goosePlacer;
	BasicBtn btn_exit;
	int selectedGoose = -1;
public:
	void init(ResourceManager& rm, MyD3D& d3d);
	void update(ResourceManager& rm, float dTime, Vector2 mousePos, bool isLMBPressed, bool keyboard[], Goose geese[], Track& track);
	void render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime, Goose geese[]);
};