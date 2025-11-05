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
#include "Bloon.h"
#include "Stats.h"

class LoseMode
{
private:
	//vector<Sprite> spr_bloons;
	//vector<Text> txt_loseMsgs;
	Text txt_loseMsg;
	Sprite spr_bg;
public:
	void init(ResourceManager& rm, MyD3D& d3d);
	Modes update(float dTime);
	void render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime);
};

