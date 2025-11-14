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
#include "StartMode.h"
#include "PlaceMode.h"
#include "DefendMode.h"
#include "LoseMode.h"
#include "WinMode.h"

class Game
{
public:
	Game(MyD3D*);
	void init();
	void release();
	void update(float dTime, Vector2 mousePos, bool isLMBPressed);
	void render(float dTime);
	void changeState();
	
private:
	MyD3D* p_d3d;
	ResourceManager rm; // game's resource manager
	DirectX::SpriteBatch* gpSpriteBatch = nullptr; 
	// timing
	int gCycle = 0;
	int gFrameCounter = 0;
	float gTime = 0;
	float gResTimer = 0;
	float gFrameTimer = 0;
	// gamemodes
	Modes mode{ Modes::place };
	StartMode startMode;
	PlaceMode placeMode;
	DefendMode defendMode;
	LoseMode loseMode;
	WinMode winMode;
	// widely used game objects
	Bloons bloons{ track };
	Goose geese[GC::MAX_GEESE];
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

};