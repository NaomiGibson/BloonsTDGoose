#include "PlaceMode.h"

void PlaceMode::init(ResourceManager& rm, MyD3D& d3d) {
	rm.loadFont(d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	spr_bg.init(rm.loadTexture(d3d, L"../bin/data/BloonsMap.dds", "mainBackground"), { 0, 0, 1920, 1080 }, { 0, 0 }, 0, { 1, 1 });
	ui_stats.init(d3d, rm, (*GameStats::GetInstance()).getLives(), (*GameStats::GetInstance()).getCoins(), (*GameStats::GetInstance()).getRound(), GC::MAX_ROUNDS);
	string texName = rm.loadTexture(d3d, L"../bin/data/PlayIcon64.dds", "playIcon64");
	btn_play.init(d3d, rm, { 64, 64 }, texName, { 0, 0, 64, 64 }, { 1840, 996 }, 0, { 1, 1 });
	texName = rm.loadTexture(d3d, L"../bin/data/ExitIcon.dds", "ExitIcon");
	btn_exit.init(d3d, rm, { 128, 128 }, texName, { 0, 0, 128, 128 }, { 84, 980 }, 0, { 1, 1 });
	ResourceManager::Spritesheet sprsheet = rm.loadSpritesheet(d3d, L"../bin/data/Geese.dds", "goose", 4, 4, 12);
	btn_placeGoose.init(d3d, rm, sprsheet, 1, { 1680, 600 }, 0, { 1, 1 });
	ui_goosePlacer.init(rm, d3d);
}
void PlaceMode::update(ResourceManager& rm, float dTime, Vector2 mousePos, bool isLMBPressed, bool keyboard[], Goose geese[], Track& track) {
	for (int i(0); i < GC::MAX_GEESE; i++) {
		geese[i].updatePlace(dTime, mousePos, isLMBPressed);
	}
	btn_play.update(dTime, mousePos, isLMBPressed);
	btn_exit.update(dTime, mousePos, isLMBPressed);
	btn_placeGoose.update(dTime, mousePos, isLMBPressed);
	if (btn_placeGoose.getButton().getIsBtnDown())
		ui_goosePlacer.activate();
	ui_goosePlacer.update(rm, mousePos, isLMBPressed, geese, track, ui_stats);
	ui_stats.update(rm, dTime);

	//After updating everything, decide current state
	if (btn_exit.getButton().getIsBtnDown())
		(*GameStats::GetInstance()).setMode(Modes::start);
	if (btn_play.getButton().getIsBtnDown())
		(*GameStats::GetInstance()).setMode(Modes::defend);
}
void PlaceMode::render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime, Goose geese[]) {
	spr_bg.render(d3d, rm, dTime, sprBatch);
	for (int i(0); i < GC::MAX_GEESE; i++) {
		geese[i].render(d3d, rm, dTime, sprBatch);
	}
	ui_stats.render(d3d, rm, dTime, sprBatch);
	btn_play.render(d3d, rm, dTime, sprBatch);
	btn_exit.render(d3d, rm, dTime, sprBatch);
	btn_placeGoose.render(d3d, rm, dTime, sprBatch);
	ui_goosePlacer.render(d3d, rm, dTime, sprBatch);
}