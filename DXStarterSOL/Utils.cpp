#pragma once
#include "Utils.h"

int GameStats::getLives() { return lives; }
void GameStats::resetLives() { lives = GC::START_LIVES; }
void GameStats::loseLife() { lives--; }
int GameStats::getCoins() { return coins; }
void GameStats::addCoins(int coins_) { coins += coins_; }
bool GameStats::spendCoins(int coins_) {
	if (coins - coins_ >= 0) {
		coins -= coins_; 
		return true;
	}
	return false;
}
void GameStats::resetCoins() { coins = GC::START_COINS; }

GameStats* GameStats::GetInstance() {
	if (instance == nullptr) {
		instance = new GameStats();
	}
	return instance;
}
int GameStats::nextRound() {
	if(round < GC::MAX_ROUNDS)
		round++; 
	return round; 
}
int GameStats::getRound() { return round; }
void GameStats::resetGame() {
	resetLives();
	resetCoins();
	round = 0;
}
float GameStats::getTimeScale() { return timeScale; }
void GameStats::setTimeScale(float timeScale_) {
	timeScale = timeScale_;
}
GameStats* GameStats::instance = nullptr; // important singleton thing