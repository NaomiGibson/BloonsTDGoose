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

class PlaceMode
{
private:
	Sprite spr_bg;
	Stats ui_stats;
	Button btn_play;
	Button btn_placeGoose;
	GoosePlacer ui_goosePlacer;
public:
	void init(ResourceManager& rm, MyD3D& d3d);
	Modes update(ResourceManager& rm, float dTime, Vector2 mousePos, bool isLMBPressed, Goose geese[], Track& track);
	void render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime, Goose geese[]);
};