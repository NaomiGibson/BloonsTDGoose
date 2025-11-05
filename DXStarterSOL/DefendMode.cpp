#include "DefendMode.h"
void DefendMode::init(ResourceManager& rm,  MyD3D& d3d) {
	rm.loadFont(d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	spr_bg.init(rm.loadTexture(d3d, L"../bin/data/BloonsMap.dds", "mainBackground"), { 0, 0, 1920, 1080 }, { 0, 0 }, 0, { 1, 1 });
	goose.init(rm, d3d);
	for (int i = 0; i < GC::MAX_BLOONS; i++) {
		bloons.emplace_back(track);
		bloons[i].init(rm, d3d);
	}
	//gameStats.init(*p_d3d, rm, lives, 0, 1);
}
Modes DefendMode::update(float dTime) {
	static float lastBloonSpawn = 0;
	float spawnRate = 0.2f;
	float time = GetClock();
	if (time - lastBloonSpawn > spawnRate) {
		for (unsigned int i = 0; i < bloons.size(); i++) {
			if (!bloons[i].getIsActive()) {
				bloons[i].activate();
				lastBloonSpawn = GetClock();
				i = bloons.size();
			}
		}
	}
	for (unsigned int i = 0; i < bloons.size(); i++) {
		if (!bloons[i].update(dTime)) {
			gameStats.loseLife();
			if (gameStats.getLives() < 0) {
				return Modes::lose;
			}
		}
	}
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
	//gameStats.render(*p_d3d, rm, dTime, sprBatch);

	sprBatch.End();
	d3d.EndRender();
}