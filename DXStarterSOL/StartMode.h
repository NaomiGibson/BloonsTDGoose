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
#include "Text.h"
#include "Button.h"

class StartMode
{
private:
	Sprite spr_bg;
	Text txt_title;
	BasicBtn btn_play;
	BasicBtn btn_exit;
public:
	StartMode() {};
	void init(ResourceManager& rm, MyD3D& d3d);
	void update(float dTime, Vector2 mousePos, bool isLMBPressed);
	void render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime);
};