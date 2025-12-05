#include "LoseMode.h"

void LoseMode::init(ResourceManager& rm, MyD3D& d3d, Track& track) {
	rm.loadFont(d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	string texName = rm.loadTexture(d3d, L"../bin/data/BloonsMap.dds", "mainBackground");
	spr_bg.init(texName, { 0, 0, 1920, 1080 }, { 0, 0 }, 0, { 1, 1 });
	// buttons
	//txt_loseMsg = Text("Moghul", "YOU LOSE!", { 512, 512 }, { 0, 0, 0, 1 });
	texName = rm.loadTexture(d3d, L"../bin/data/PlayIcon.dds", "playIcon");
	btn_reset.init(d3d, rm, { 256, 256 }, texName, { 0, 0, 256, 256 }, { 1680, 744 }, 0, { 1, 1 });
	btn_reset.initText("Moghul", "Reset", { -55, -16 }, { 0, 0, 0, 1 });
	ui_stats.init(d3d, rm, (*GameStats::GetInstance()).getLives(), (*GameStats::GetInstance()).getCoins(), (*GameStats::GetInstance()).getRound(), GC::MAX_ROUNDS);
	// you lose message bloons
	bloons.resize(8);
	for (int i(0); i < bloons.size(); i++) {
		bloons[i].init(rm, d3d, track, msgBloonProgress[i], string(1, loseMsg[i]), 1);
	}
}
void LoseMode::update(float dTime, Vector2 mousePos, bool isLMBPressed) {
	btn_reset.update(dTime, mousePos, isLMBPressed);
	if (btn_reset.getButton().getIsBtnDown())
		(*GameStats::GetInstance()).setMode(Modes::place);
}
void LoseMode::render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime) {
	spr_bg.render(d3d, rm, dTime, sprBatch);
	for (int i(0); i < bloons.size(); i++) {
		bloons[i].render(rm, d3d, dTime, sprBatch);
	}
	btn_reset.render(d3d, rm, dTime, sprBatch);
	ui_stats.render(d3d, rm, dTime, sprBatch);
}