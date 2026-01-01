#include "Stats.h"

void Stats::init(MyD3D& d3d, ResourceManager& rm, int lives, int coins, int round, int maxRounds) {
	spr_lives.init(rm.loadTexture(d3d, L"../bin/data/LivesIcon.dds", "livesIcon"), { 0, 0, 32, 32 }, {txt_lives.getPos().x - 32, txt_lives.getPos().y}, 0, {1, 1});
	spr_coins.init(*(rm.findSpritesheet(rm.loadSpritesheet(d3d, L"../bin/data/CoinSpin.dds", "coinSpin", 4, 2, 6))), 1, { txt_coins.getPos().x - 32, txt_coins.getPos().y }, 0, { 1, 1 });
	setLives(lives);
	setCoins(coins);
	setRound(round, maxRounds);
}
void Stats::update(ResourceManager& rm, float dTime) {
	anim_coinSpin.update(rm, dTime);
}
void Stats::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	txt_round.render(d3d, rm, dTime, batch);
	spr_lives.render(d3d, rm, dTime, batch);
	txt_lives.render(d3d, rm, dTime, batch);
	spr_coins.render(d3d, rm, dTime, batch);
	txt_coins.render(d3d, rm, dTime, batch);
}
void Stats::setLives(int lives) {
	string newMsg = to_string(lives);
	txt_lives.setMsg(newMsg);
}
void Stats::setCoins(int coins) {
	string newMsg = to_string(coins);
	anim_coinSpin.play(true);
	txt_coins.setMsg(newMsg);
}
void Stats::setRound(int round, int maxRounds) {
	string newMsg = "Round " + to_string(round + 1) + " / " + to_string(maxRounds);
	txt_round.setMsg(newMsg);
}