#include "PlaceMode.h"

void PlaceMode::init(ResourceManager& rm, MyD3D& d3d) {
	rm.loadFont(d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	spr_bg.init(rm.loadTexture(d3d, L"../bin/data/BloonsMap.dds", "mainBackground"), { 0, 0, 1920, 1080 }, { 0, 0 }, 0, { 1, 1 });
	ui_stats.init(d3d, rm, gameStats.getLives(), gameStats.getCoins(), gameStats.getRound());
	string texName = rm.loadTexture(d3d, L"../bin/data/PlayIcon64.dds", "playIcon64");
	btn_play.init(d3d, rm, { 64, 64 }, texName, { 0, 0, 64, 64 }, { 1840, 996 }, 0, { 1, 1 });
	ResourceManager::Spritesheet sprsheet = rm.loadSpritesheet(d3d, L"../bin/data/Geese.dds", "goose", 4, 4, 12);
	btn_placeGoose.init(d3d, rm, sprsheet, 1, { 1680, 800 }, 0, { 1, 1 });
	ui_goosePlacer.init(rm, d3d);
}
Modes PlaceMode::update(float dTime, Vector2 mousePos, bool isLMBPressed) {
	btn_play.update(dTime, mousePos, isLMBPressed);
	if (btn_play.getIsBtnDown())
		return Modes::defend;
	btn_placeGoose.update(dTime, mousePos, isLMBPressed);
	if (btn_placeGoose.getIsBtnDown())
		ui_goosePlacer.activate();
	ui_goosePlacer.update(mousePos, isLMBPressed);
	return Modes::place;
}
void PlaceMode::render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime) {
	spr_bg.render(d3d, rm, dTime, sprBatch);
	ui_stats.render(d3d, rm, dTime, sprBatch);
	btn_play.render(d3d, rm, dTime, sprBatch);
	btn_placeGoose.render(d3d, rm, dTime, sprBatch);
	ui_goosePlacer.render(d3d, rm, dTime, sprBatch);
}