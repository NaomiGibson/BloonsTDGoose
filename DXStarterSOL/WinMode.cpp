#include "WinMode.h"

void WinMode::init(ResourceManager& rm, MyD3D& d3d, Track& track) {
	rm.loadFont(d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	string texName = rm.loadTexture(d3d, L"../bin/data/BloonsMap.dds", "mainBackground");
	// buttons
	spr_bg.init(texName, { 0, 0, 1920, 1080 }, { 0, 0 }, 0, { 1, 1 });
	texName = rm.loadTexture(d3d, L"../bin/data/PlayIcon.dds", "playIcon");
	btn_reset.init(d3d, rm, { 256, 256 }, texName, { 0, 0, 256, 256 }, { 1680, 744 }, 0, { 1, 1 });
	btn_reset.initText("Moghul", "Reset", { -55, -16 }, { 0, 0, 0, 1 });
	texName = rm.loadTexture(d3d, L"../bin/data/ExitIcon.dds", "ExitIcon");
	btn_exit.init(d3d, rm, { 128, 128 }, texName, { 0, 0, 128, 128 }, { 84, 980 }, 0, { 1, 1 });
	ui_stats.init(d3d, rm, (*GameStats::GetInstance()).getLives(), (*GameStats::GetInstance()).getCoins(), (*GameStats::GetInstance()).getRound(), GC::MAX_ROUNDS);
	// message bloons
	bloons.resize(7);
	for (int i(0); i < bloons.size(); i++) {
		bloons[i].init(rm, d3d, track, msgBloonProgress[i], string(1, loseMsg[i]));
	}

}
void WinMode::update(float dTime, Vector2 mousePos, bool isLMBPressed) {
	btn_reset.update(dTime, mousePos, isLMBPressed);
	if (btn_reset.getButton().getIsBtnDown())
		(*GameStats::GetInstance()).setMode(Modes::place);
	btn_exit.update(dTime, mousePos, isLMBPressed);
	if (btn_exit.getButton().getIsBtnDown())
		(*GameStats::GetInstance()).setMode(Modes::start);
}
void WinMode::render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime) {
	spr_bg.render(d3d, rm, dTime, sprBatch);
	for (int i(0); i < bloons.size(); i++) {
		bloons[i].render(rm, d3d, dTime, sprBatch);
	}
	btn_reset.render(d3d, rm, dTime, sprBatch);
	btn_exit.render(d3d, rm, dTime, sprBatch);
	ui_stats.render(d3d, rm, dTime, sprBatch);
}