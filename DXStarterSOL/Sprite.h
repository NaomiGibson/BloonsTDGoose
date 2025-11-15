#pragma once
#include <windows.h>
#include <string>
#include <cassert>
#include <d3d11.h>
#include <iomanip>
#include <vector>

#include "SimpleMath.h"
#include "SpriteFont.h"
#include "DDSTextureLoader.h"
#include "CommonStates.h"
#include "ResourceManager.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class Sprite
{
public:
	Sprite::Sprite() {};
	void init(string texName_, RECT texRect_, Vector2 pos_, float rotation_, Vector2 scale_); // initialise sprite with a whole texture
	void init(ResourceManager::Spritesheet sprSheet, int sprID, Vector2 pos_, float rotation_, Vector2 scale_); // initialise sprite with spritesheet
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	string getTexName();
	void setTexName(string texName);
	RECT getTexRect();
	void setTexRect(RECT texRect_);
	Vector2 getOrigin();
	void setOrigin(Vector2 origin_);
	Vector2 getPos();
	void setPos(Vector2 pos_);
	float getRotation();
	void setRotation(float rotation_);
	void Sprite::setRotationRads(float rads);
	Vector2 getScale();
	void setScale(const Vector2& scale_);
	Vector2 GetScreenSize();

protected:
	string texName{ "default" };
	RECT texRect{ 0, 0, 0, 0 };
	Vector2 origin{ 0, 0 };
	Vector2 pos{ 0, 0 };
	float rotation{ 0 };
	Vector2 scale{ 1, 1 };
};

class SpriteAnimation
{
private:
	//string texName;			// for looking up in resource manager
	int mStart = 0, mStop = 0, mCurrent = 0; //start, stop and current frame of animation
	float mRateSec = 0;		//how fast to play back
	float mElapsedSec = 0;	//how long the current frame has been on screen
	bool mLoop = false;		//loop at the end ?
	bool mPlay = false;		//should we be playing right now
	Sprite& mSpr;			//the parent sprite
public:
	SpriteAnimation(Sprite& spr_, int startFrame, int endFrame, float rateSec, bool loop) : mSpr(spr_) {
		assert(endFrame > startFrame);
		mStart = startFrame;
		mStop = endFrame;
		mCurrent = mStart;
		mRateSec = rateSec;
		mLoop = loop;
	};
	~SpriteAnimation() {
	}
	Sprite& getSpr() { return mSpr; }
	void update(ResourceManager& rm, float dTime);
	void play(bool play) { mPlay = play; }
};
