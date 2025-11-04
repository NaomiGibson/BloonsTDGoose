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


#include "utils.cpp"
#include "ResourceManager.h"
#include "Sprite.h"
#include "Goose.h"
#include "Bloon.h"
#include "Stats.h"

class LoseMode
{
public:
	void init(ResourceManager& rm, MyD3D& d3d);
	void release();
	Modes update(float dTime);
	void render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime);
};

