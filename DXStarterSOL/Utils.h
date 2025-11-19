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
	const int START_COINS = 30;
	const int GOOSE_COST = 20;
	const int MAX_BLOONS = 500;
	const float BLOON_SPAWN_RATE = 0.2f;
	const int MAX_ROUNDS = 5;
	const int MAX_PROJECTILES = 60;
	const int MAX_GEESE = 20;

	const int BLOONS_PER_ROUND = 100;
};
class GameStats {
private:
	static GameStats* instance;					// important singleton thing
	GameStats() {}								// important singleton thing
	int lives{ GC::START_LIVES };
	int coins{ GC::START_COINS };
	int round{ 0 };
	float timeScale{ 1 };
	Modes mode{ Modes::start };
public:
	static GameStats* GetInstance();			 // important singleton thing
	GameStats(const GameStats& obj) = delete;	 // important singleton thing

	int getLives();
	void resetLives();
	void loseLife();
	int getCoins();
	void addCoins(int coins_);
	// @return true if player can afford to spend the coins
	bool spendCoins(int coins_);
	void resetCoins();
	int nextRound();
	int getRound();
	void resetGame();
	float getTimeScale();
	void setTimeScale(float timeScale_);
	Modes getMode() { return mode; }
	void setMode(Modes mode_) { mode = mode_; }
};