#include "DefendMode.h"
void DefendMode::init(ResourceManager& rm,  MyD3D& d3d) {
	rm.loadFont(d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	spr_bg.init(rm.loadTexture(d3d, L"../bin/data/BloonsMap.dds", "mainBackground"), { 0, 0, 1920, 1080 }, { 0, 0 }, 0, { 1, 1 });
	goose.init(rm, d3d);
	projectiles.init(rm, d3d);
	bloons.init(rm, d3d);
	ui_stats.init(d3d, rm, gameStats.getLives(), gameStats.getCoins(), gameStats.getRound());
	track.init();
}
void DefendMode::handleCollision(ResourceManager& rm) {
	// BLOON V GOOSE COLLISION		 FOR DEBUG ONLY
	bool isGooseColliding = false;
	for (int i = 0; i < GC::MAX_BLOONS; i++) {
		Collider& coll_bloon = bloons.getCollider(i);
		bool isColliding = goose.getRangeCollider().isColliding(coll_bloon);
		if (isColliding) isGooseColliding = true;
	}
	goose.getRangeCollider().onCollision(rm, isGooseColliding);

	// PROJECTILE V BLOON COLLISION
	for (int b(0); b < GC::MAX_BLOONS; b++) {										//for each active
		if (bloons.getIsActive(b)) {												//pair of bloons
			for (int p(0); p < GC::MAX_PROJECTILES; p++) {							//and projectiles
				if (projectiles.getIsActive(p)) {									//
					Collider& coll_bloon = bloons.getCollider(b);
					Collider& coll_projectile = projectiles.getCollider(b);
					if (coll_bloon.isColliding(coll_projectile)) {					// if they are overlapping, call appropriate functions
						bloons.onCollision_projectile(b);
						projectiles.onCollision_bloon(p);
						ui_stats.setCoins(gameStats.getCoins());					// update ui to reflect coins gained from popping bloon
					}
				}
			}
		}
	}
}
Modes DefendMode::update(ResourceManager& rm, float dTime) {
	if (bloons.update(dTime)) {
		ui_stats.setLives(gameStats.getLives());
	}
	goose.update(dTime, bloons, projectiles);
	projectiles.update(dTime);
	handleCollision(rm);

	// After updating everything, decide final state
	if (gameStats.getLives() < 0)
		return Modes::lose;
	else
		return Modes::defend;
}
void DefendMode::render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime) {
	spr_bg.render(d3d, rm, 0, sprBatch);
	projectiles.render(d3d, rm, dTime, sprBatch);
	goose.render(d3d, rm, 0, sprBatch);
	bloons.render(d3d, rm, dTime, sprBatch);
	ui_stats.render(d3d, rm, dTime, sprBatch);
}