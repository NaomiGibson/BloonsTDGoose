#include "LoseMode.h"

void LoseMode::init(ResourceManager& rm, MyD3D& d3d) {
	rm.loadFont(d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	string texName = rm.loadTexture(d3d, L"../bin/data/BloonsMap.dds", "mainBackground");
	spr_bg.init(texName, { 0, 0, 1920, 1080 }, { 0, 0 }, 0, { 1, 1 });
	// buttons
	txt_loseMsg = Text("Moghul", "YOU LOSE!", { 512, 512 }, { 0, 0, 0, 1 });
	texName = rm.loadTexture(d3d, L"../bin/data/PlayIcon.dds", "playIcon");
	btn_reset.init(d3d, rm, { 256, 256 }, texName, { 0, 0, 256, 256 }, { 1680, 744 }, 0, { 1, 1 });
	btn_reset.initText("Moghul", "Reset", { -55, -16 }, { 0, 0, 0, 1 });
	texName = rm.loadTexture(d3d, L"../bin/data/ExitIcon.dds", "ExitIcon");
	btn_exit.init(d3d, rm, { 128, 128 }, texName, { 0, 0, 128, 128 }, { 84, 980 }, 0, { 1, 1 });

	ui_stats.init(d3d, rm, (*GameStats::GetInstance()).getLives(), (*GameStats::GetInstance()).getCoins(), (*GameStats::GetInstance()).getRound());
}
Modes LoseMode::update(float dTime, Vector2 mousePos, bool isLMBPressed) {
	btn_reset.update(dTime, mousePos, isLMBPressed);
	if (btn_reset.getIsBtnDown())
		return Modes::place;
	btn_exit.update(dTime, mousePos, isLMBPressed);
	if (btn_exit.getIsBtnDown())
		return Modes::start;
	return Modes::lose;
}
void LoseMode::render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime) {
	spr_bg.render(d3d, rm, dTime, sprBatch);
	txt_loseMsg.render(d3d, rm, dTime, sprBatch);
	btn_reset.render(d3d, rm, dTime, sprBatch);
	btn_exit.render(d3d, rm, dTime, sprBatch);
	ui_stats.render(d3d, rm, dTime, sprBatch);
}