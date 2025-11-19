#include "DefendMode.h"
void DefendMode::init(ResourceManager& rm,  MyD3D& d3d, Goose geese[], Bloons& bloons) {
	rm.loadFont(d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	spr_bg.init(rm.loadTexture(d3d, L"../bin/data/BloonsMap.dds", "mainBackground"), { 0, 0, 1920, 1080 }, { 0, 0 }, 0, { 1, 1 });
	string texName = rm.loadTexture(d3d, L"../bin/data/FastForwardIcon.dds", "fastForwardIcon");
	rm.loadTexture(d3d, L"../bin/data/PlayIcon64.dds", "playIcon64");
	btn_gameSpeed.init(d3d, rm, { 64, 64 }, texName, { 0, 0, 64, 64 }, { 1840, 996 }, 0, { 1, 1 });
	ResourceManager::Spritesheet sprsheetName = rm.loadSpritesheet(d3d, L"../bin/data/EnvironmentTiles.dds", "environmentTiles", 4, 4, 14);
	spr_bridge1.init(sprsheetName, 14, { 192, 312 }, 0, { 1, 1 });
	spr_bridge2.init(sprsheetName, 13, { 672, 792 }, 0, { 1, 1 });
	projectiles.init(rm, d3d);
	ui_stats.init(d3d, rm, (*GameStats::GetInstance()).getLives(), (*GameStats::GetInstance()).getCoins(), (*GameStats::GetInstance()).getRound(), GC::MAX_ROUNDS);
}
void DefendMode::handleCollision(ResourceManager& rm, Bloons& bloons) {
	// BLOON V GOOSE COLLISION		 FOR DEBUG ONLY
	//bool isGooseColliding = false;
	//for (int i = 0; i < GC::MAX_BLOONS; i++) {
	//	Collider& coll_bloon = bloons.getCollider(i);
	//	bool isColliding = goose.getRangeCollider().isColliding(coll_bloon);
	//	if (isColliding) isGooseColliding = true;
	//}
	//goose.getRangeCollider().onCollision(rm, isGooseColliding);

	// PROJECTILE V BLOON COLLISION
	for (int i_bloon(0); i_bloon < GC::MAX_BLOONS; i_bloon++) {										//for each active
		if (bloons.getIsActive(i_bloon)) {															//pair of bloons
			for (int i_projectile(0); i_projectile < GC::MAX_PROJECTILES; i_projectile++) {			//and projectiles
				if (projectiles.getIsActive(i_projectile)) {										//
					Collider& coll_bloon = bloons.getCollider(i_bloon);
					Collider& coll_projectile = projectiles.getCollider(i_projectile);
					if (coll_bloon.isColliding(coll_projectile)) {									// if they are overlapping, call appropriate functions
						bloons.onCollision_projectile(i_bloon);
						projectiles.onCollision_bloon(i_projectile);
						ui_stats.setCoins((*GameStats::GetInstance()).getCoins());					// update ui to reflect coins gained from popping bloon
					}
				}
			}
		}
	}
}
void DefendMode::update(ResourceManager& rm, float dTime, Vector2 mousePos, bool isLMBPressed, bool keyboard[], Goose geese[], Bloons& bloons) {
	// Update Game Objects
	if (bloons.update(dTime)) {
		ui_stats.setLives((*GameStats::GetInstance()).getLives());
	}
	for (int i(0); i < GC::MAX_GEESE; i++) {
		geese[i].updateDefend(dTime, bloons, projectiles, mousePos, isLMBPressed);
	}
	projectiles.update(dTime);
	// speed up button
	isGameSpeedBtnDown = btn_gameSpeed.getButton().getIsBtnDown(); // hold last value so that speed is only togled once for each click
	btn_gameSpeed.update(dTime, mousePos, isLMBPressed);
	if (btn_gameSpeed.getButton().getIsBtnDown() && !isGameSpeedBtnDown)
		toggleTimeScale();

	//handle collision
	handleCollision(rm, bloons);

	// After updating everything, decide final state
	if ((*GameStats::GetInstance()).getLives() == 0)
		(*GameStats::GetInstance()).setMode(Modes::lose);
	if (bloons.isRoundFinished() && bloons.getNumActiveBloons() == 0) {
		bloons.endRound();
		if (bloons.areAllRoundsFinished() && bloons.getNumActiveBloons() == 0)
			(*GameStats::GetInstance()).setMode(Modes::win);
		(*GameStats::GetInstance()).setMode(Modes::place);
	}
}
void DefendMode::render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime, Goose geese[], Bloons& bloons) {
	spr_bg.render(d3d, rm, dTime, sprBatch);
	bloons.render(d3d, rm, dTime, sprBatch, 2);
	spr_bridge2.render(d3d, rm, dTime, sprBatch);
	bloons.render(d3d, rm, dTime, sprBatch, 1);
	spr_bridge1.render(d3d, rm, dTime, sprBatch);
	bloons.render(d3d, rm, dTime, sprBatch, 0);
	projectiles.render(d3d, rm, dTime, sprBatch);
	for (int i(0); i < GC::MAX_GEESE; i++) {
		geese[i].render(d3d, rm, dTime, sprBatch);
	}
	ui_stats.render(d3d, rm, dTime, sprBatch);
	btn_gameSpeed.render(d3d, rm, dTime, sprBatch);
}
void DefendMode::reset(Bloons& bloons) {
	(*GameStats::GetInstance()).resetGame();
	bloons.reset();
}
void DefendMode::toggleTimeScale() {
	if (isGameFast) {
		(*GameStats::GetInstance()).setTimeScale(1);
		btn_gameSpeed.getSpr().setTexName("fastForwardIcon");
		isGameFast = false;
	}
	else {
		(*GameStats::GetInstance()).setTimeScale(FAST_TIME_SCALE);
		btn_gameSpeed.getSpr().setTexName("playIcon64");
		isGameFast = true;
	}
}