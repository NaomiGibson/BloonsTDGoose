#pragma once
#include "Sprite.h"
#include "Text.h"

class Stats
{
private:
	Text txt_round{ "Moghul", "Round 1/10", {1700, 50} , Colours::Black };
	Sprite spr_lives;
	Text txt_lives{ "Moghul", "Lives", {1500, 980}, Colours::Black };
	Sprite spr_coins;
	Text txt_coins{ "Moghul", "Coins", {1700, 980}, Colours::Black };
public:
	void init(MyD3D& d3d, ResourceManager& rm, int lives, int coins, int round);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	void setLives(int lives);
	void setCoins(int coins);
	void setRound(int round);
};