#include "DefendMode.h"
void DefendMode::init(ResourceManager& rm,  MyD3D& d3d) {
	rm.loadFont(d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	spr_bg.init(rm.loadTexture(d3d, L"../bin/data/BloonsMap.dds", "mainBackground"), { 0, 0, 1920, 1080 }, { 0, 0 }, 0, { 1, 1 });
	goose.init(rm, d3d);
	bloons.init(rm, d3d);
	ui_stats.init(d3d, rm, gameStats.getLives(), gameStats.getCoins(), gameStats.getRound());
	track.init();
}
void DefendMode::handleCollision(ResourceManager& rm) {
	// BLOON V GOOSE COLLISION
	bool isGooseColliding = false;
	for (int i = 0; i < GC::MAX_BLOONS; i++) {
		Collider& coll_bloon = bloons.getCollider(i);
		bool isColliding = goose.getRangeCollider().isColliding(coll_bloon);
		if (isColliding) isGooseColliding = true;
	}
	goose.getRangeCollider().onCollision(rm, isGooseColliding);
}
Modes DefendMode::update(ResourceManager& rm, float dTime) {
	if (bloons.update(dTime)) {
		ui_stats.setLives(gameStats.getLives());
	}
	goose.update(dTime, bloons);
	handleCollision(rm);

	// After updating everything, decide final state
	if (gameStats.getLives() < 0)
		return Modes::lose;
	else
		return Modes::defend;
}
void DefendMode::render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime) {
	spr_bg.render(d3d, rm, 0, sprBatch);
	goose.render(d3d, rm, 0, sprBatch);
	bloons.render(d3d, rm, dTime, sprBatch);
	ui_stats.render(d3d, rm, dTime, sprBatch);
}