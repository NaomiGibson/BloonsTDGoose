#pragma once
enum Modes {
	start,
	place,
	defend,
	win,
	lose
};
namespace GC {
	const int START_LIVES = 50;
	const int NUM_ROUNDS = 10;
	const int MAX_BLOONS = 50;
	const float BLOON_SPAWN_RATE = 0.2f;
	const int MAX_ROUNDS = 10;
	const int MAX_PROJECTILES = 4;

	const int BLOONS_PER_ROUND = 20;
};
class GameStats {
private:
	static GameStats* instance;
	int lives{ GC::START_LIVES };
	int coins{ 0 };
	int round{ 0 };
	GameStats() {}
public:
	static GameStats* GetInstance();
	GameStats(const GameStats& obj) = delete;

	int getLives();
	void resetLives();
	void loseLife();
	int getCoins();
	void addCoins(int coins_);
	void resetCoins();
	int nextRound();
	int getRound();
	void resetGame();
};