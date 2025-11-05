#pragma once
enum Modes {
	start,
	place,
	defend,
	win,
	lose
};
namespace GC {
	const int START_LIVES = 200;
	const int NUM_ROUNDS = 10;
	const int MAX_BLOONS = 100;
}
struct GameStats {
private:
	int lives{ GC::START_LIVES };
	int coins{ 0 };
	int round = 0;
public:
	int getLives() { return lives; }
	void resetLives() { lives = GC::START_LIVES; }
	void loseLife() { lives--; }
	int getCoins() { return coins; }
	void addCoins(int coins_) { coins += coins_; }
	void resetCoins(int coins_) { coins = 0; }
	int nextRound() { 
		round++; 
		return round; 
	}
}; 
static GameStats gameStats;