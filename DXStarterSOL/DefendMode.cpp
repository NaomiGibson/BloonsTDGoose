#include "DefendMode.h"
void DefendMode::init(ResourceManager& rm,  MyD3D& d3d) {
	reset();
	rm.loadFont(d3d, L"../bin/data/Moghul.spritefont", "Moghul");

	spr_test.init(rm.loadSpritesheet(d3d, L"../bin/data/Geese.dds", "goose", 4, 4, 5), 2, { 1700, 700 }, 0, { 1, 1 });
	Vector2 source = { 0 , 0 };
	Vector2 tgt = { 1, 0 };
	Vector2 vec_direction = {  tgt.x - source.x, tgt.y - source.y };
	float direction = atan2(vec_direction.y, vec_direction.x);
	spr_test.setRotationRads(direction);

	spr_bg.init(rm.loadTexture(d3d, L"../bin/data/BloonsMap.dds", "mainBackground"), { 0, 0, 1920, 1080 }, { 0, 0 }, 0, { 1, 1 });
	ResourceManager::Spritesheet texName = rm.loadSpritesheet(d3d, L"../bin/data/EnvironmentTiles.dds", "environmentTiles", 4, 4, 14);
	spr_bridge1.init(texName, 14, { 192, 312 }, 0, { 1, 1 });
	spr_bridge2.init(texName, 13, { 672, 792 }, 0, { 1, 1 });
	goose.init(rm, d3d, { 432, 260 });
	goose2.init(rm, d3d, { 336, 164 });
	goose3.init(rm, d3d, { 644, 708 });
	projectiles.init(rm, d3d);
	bloons.init(rm, d3d);
	ui_stats.init(d3d, rm, (*GameStats::GetInstance()).getLives(), (*GameStats::GetInstance()).getCoins(), (*GameStats::GetInstance()).getRound());
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
					Collider& coll_projectile = projectiles.getCollider(p);
					if (coll_bloon.isColliding(coll_projectile)) {					// if they are overlapping, call appropriate functions
						bloons.onCollision_projectile(b);
						projectiles.onCollision_bloon(p);
						ui_stats.setCoins((*GameStats::GetInstance()).getCoins());					// update ui to reflect coins gained from popping bloon
					}
				}
			}
		}
	}
}
Modes DefendMode::update(ResourceManager& rm, float dTime, float timeScale) {
	if (bloons.update(dTime, timeScale)) {
		ui_stats.setLives((*GameStats::GetInstance()).getLives());
	}
	goose.update(dTime, timeScale, bloons, projectiles);
	goose2.update(dTime, timeScale, bloons, projectiles);
	goose3.update(dTime, timeScale, bloons, projectiles);
	projectiles.update(dTime);

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
	goose.render(d3d, rm, dTime, sprBatch);
	goose2.render(d3d, rm, dTime, sprBatch);
	goose3.render(d3d, rm, dTime, sprBatch);
	ui_stats.render(d3d, rm, dTime, sprBatch);

	spr_test.render(d3d, rm, dTime, sprBatch);
}
void DefendMode::reset() {
	(*GameStats::GetInstance()).resetGame();
	bloons.reset();
}