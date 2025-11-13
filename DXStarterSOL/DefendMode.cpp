#include "DefendMode.h"
void DefendMode::init(ResourceManager& rm,  MyD3D& d3d) {
	reset();
	rm.loadFont(d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	spr_bg.init(rm.loadTexture(d3d, L"../bin/data/BloonsMap.dds", "mainBackground"), { 0, 0, 1920, 1080 }, { 0, 0 }, 0, { 1, 1 });
	ResourceManager::Spritesheet texName = rm.loadSpritesheet(d3d, L"../bin/data/EnvironmentTiles.dds", "environmentTiles", 4, 4, 14);
	spr_bridge1.init(texName, 14, { 192, 312 }, 0, { 1, 1 });
	spr_bridge2.init(texName, 13, { 672, 792 }, 0, { 1, 1 });
	for (int i = 0; i < GC::MAX_GEESE; i++) {
		geese[i].init(rm, d3d);
	}
	//goose.init{ 432, 260 }{ 336, 164 }{ 644, 708 };
	projectiles.init(rm, d3d);
	bloons.init(rm, d3d);
	ui_stats.init(d3d, rm, (*GameStats::GetInstance()).getLives(), (*GameStats::GetInstance()).getCoins(), (*GameStats::GetInstance()).getRound());
	track.init();

}
void DefendMode::handleCollision(ResourceManager& rm) {
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
Modes DefendMode::update(ResourceManager& rm, float dTime, float timeScale) {
	// Update Game Objects
	if (bloons.update(dTime, timeScale)) {
		ui_stats.setLives((*GameStats::GetInstance()).getLives());
	}
	for (int i(0); i < GC::MAX_GEESE; i++) {
		geese[i].update(dTime, timeScale, bloons, projectiles);
	}
	projectiles.update(dTime);

	//handle collision
	handleCollision(rm);

	// After updating everything, decide final state
	if ((*GameStats::GetInstance()).getLives() < 0)
		return Modes::lose;
	else if (bloons.getBloonsSpawned() >= GC::BLOONS_PER_ROUND && bloons.getNumActiveBloons() == 0)
		return Modes::win;
	else
		return Modes::defend;
}
void DefendMode::render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime) {
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
}
void DefendMode::reset() {
	(*GameStats::GetInstance()).resetGame();
	bloons.reset();
}