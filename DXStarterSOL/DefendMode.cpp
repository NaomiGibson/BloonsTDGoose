#include "DefendMode.h"
void DefendMode::init(ResourceManager& rm,  MyD3D& d3d) {
	rm.loadFont(d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	spr_bg.init(rm.loadTexture(d3d, L"../bin/data/BloonsMap.dds", "mainBackground"), { 0, 0, 1920, 1080 }, { 0, 0 }, 0, { 1, 1 });
	goose.init(rm, d3d);
	for (int i = 0; i < GC::MAX_BLOONS; i++) {
		bloons.emplace_back(track);
		bloons[i].init(rm, d3d);
	}
	ui_stats.init(d3d, rm, gameStats.getLives(), gameStats.getCoins(), gameStats.getRound());
}
void DefendMode::spawnBloon() {
	static float lastBloonSpawn = 0;
	float time = GetClock();
	if (time - lastBloonSpawn > GC::BLOON_SPAWN_RATE) {			// at the set bloon spawn rate
		for (unsigned int i = 0; i < bloons.size(); i++) {
			if (!bloons[i].getIsActive()) {						// search for an inactive bloon
				bloons[i].activate();							// and activate it
				lastBloonSpawn = GetClock();
				i = bloons.size();
			}
		}
	}
}
void DefendMode::updateBloons(float dTime) {
	for (unsigned int i = 0; i < bloons.size(); i++) {
		if (!bloons[i].update(dTime)) {
			gameStats.loseLife();
			ui_stats.setLives(gameStats.getLives());
		}
	}
}
Modes DefendMode::update(float dTime) {
	spawnBloon();
	updateBloons(dTime);

	// After updating everything, decide final state
	if (gameStats.getLives() < 0)
		return Modes::lose;
	else
		return Modes::defend;
}
void DefendMode::render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime) {
	d3d.BeginRender({ 0, 0, 0, 0 });
	CommonStates dxstate(&d3d.GetDevice());
	sprBatch.Begin(SpriteSortMode_Deferred, dxstate.NonPremultiplied());

	spr_bg.render(d3d, rm, 0, sprBatch);
	goose.render(d3d, rm, 0, sprBatch);
	for (unsigned int i = 0; i < bloons.size(); i++) {
		bloons[i].render(d3d, rm, 0, sprBatch);
	}
	ui_stats.render(d3d, rm, dTime, sprBatch);

	sprBatch.End();
	d3d.EndRender();
}