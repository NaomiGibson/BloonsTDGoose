#pragma once
#include <unordered_map>
#include <string>
#include <d3d11.h>
#include "SimpleMath.h"

using namespace std; 
using namespace DirectX;
using namespace DirectX::SimpleMath;


enum Modes {
	start,
	place,
	defend,
	win,
	lose,
	quit
};
enum upgrades {
	projectileReinforcement_1,
	projectileReinforcement_2,
	quickFire_1,
	quickFire_2,
	longDistance_1,
	longDistance_2,
	none
};
namespace GC {
	const int START_LIVES = 50;
	const int START_COINS = 30;
	const int GOOSE_COST = 25;
	const int MAX_BLOONS = 500;
	const float BLOON_SPAWN_RATE = 0.2f;
	const int BLOONS_PER_ROUND = 100;
	const int MAX_BLOON_HEALTH = 5;
	const int MAX_ROUNDS = 10;
	const int MAX_PROJECTILES = 60;
	const int MAX_GEESE = 20;
	const Vector4 DARK_GREEN = { 23, 47, 23, 1 };

	const unordered_map<upgrades, string> UPGRADE_NAMES = {
		{ projectileReinforcement_1,	"Projectile Reinforcement 1" },
		{ projectileReinforcement_2,	"Projectile Reinforcement 2" },
		{ quickFire_1,					"Quick Fire 1" },
		{ quickFire_2,					"Quick Fire 2" },
		{ longDistance_1,				"Long Distance 1" },
		{ longDistance_2,				"Long Distance 2" },
		{ none,							"End of Path" }
	};
	const unordered_map<upgrades, int> UPGRADE_PRICES = {
		{ projectileReinforcement_1,	10 },
		{ projectileReinforcement_2,	15 },
		{ quickFire_1,					10 },
		{ quickFire_2,					15 },
		{ longDistance_1,				5 },
		{ longDistance_2,				10 },
		{ none,							0	}
	};
	typedef unordered_map<upgrades, bool> upgradeInfo;
};
class GameStats {
private:
	static GameStats* instance;					
	GameStats() {}								
	int lives{ GC::START_LIVES };
	int coins{ GC::START_COINS };
	int round{ 0 };
	float timeScale{ 1 };
	Modes mode{ Modes::start };
public:
	static GameStats* GetInstance();			
	GameStats(const GameStats& obj) = delete;	

	int getLives();
	void resetLives();
	void loseLife();
	void loseLives(int livesLost);
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