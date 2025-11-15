#pragma once
#include "Sprite.h"
#include "Text.h"

class Stats
{
private:
	Sprite spr_lives;
	Sprite spr_coins;
	Text txt_round{ "Moghul", "Round 1/10", {1700, 50} , Colours::Black };
	Text txt_lives{ "Moghul", "Lives", {1500, 980}, Colours::Black };
	Text txt_coins{ "Moghul", "Coins", {1700, 980}, Colours::Black };
	SpriteAnimation anim_coinSpin{ spr_coins, 1, 6, 32, false };

public:
	void init(MyD3D& d3d, ResourceManager& rm, int lives, int coins, int round);
	void update(ResourceManager& rm, float dTime);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	void setLives(int lives);
	void setCoins(int coins);
	void setRound(int round);
};