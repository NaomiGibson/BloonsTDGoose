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
#include "Msg_Bloon.h"

class StartMode
{
private:
	vector<Msg_Bloon> bloons;
	string loseMsg = "BLOONSTOWERDEFENCEGEESE";
	float msgBloonProgress[23]{  /*bloons*/ 1824, 2016, 2208, 2400, 2592, 2784, /*tower*/ 96, 192, 288, 384, 480, /*defence*/ 6528, 6432, 6336, 6240, 6144, 6048, 5952, /*geese*/ 4416, 4320, 4224, 4128, 4032};

	Sprite spr_bg;
	BasicBtn btn_play;
public:
	StartMode() {};
	void init(ResourceManager& rm, MyD3D& d3d, Track& track);
	void update(float dTime, Vector2 mousePos, bool isLMBPressed);
	void render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime);
};