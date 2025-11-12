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
	const int MAX_BLOONS = 50;
	const float BLOON_SPAWN_RATE = 0.2;
	const int MAX_ROUNDS = 10;
	const int MAX_PROJECTILES = 4;

	const int BLOONS_PER_ROUND = 20;
}
struct GameStats {
private:
	int lives{ GC::START_LIVES };
	int coins{ 0 };
	int round{ 0 };
public:
	int getLives() { return lives; }
	void resetLives() { lives = GC::START_LIVES; }
	void loseLife() { lives--; }
	int getCoins() { return coins; }
	void addCoins(int coins_) { coins += coins_; }
	void resetCoins() { coins = 0; }
	int nextRound() { 
		round++; 
		return round; 
	}
	int getRound() { return round; }
	void resetGame() {
		resetLives();
		resetCoins();
		round = 0;
	}
	//static GameStats::GetSingleton() {
	//
	//}
}; 
static GameStats gameStats;
