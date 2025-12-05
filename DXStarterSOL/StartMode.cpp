#include "StartMode.h"
void StartMode::init(ResourceManager& rm, MyD3D& d3d, Track& track) {
	rm.loadFont(d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	string texName = rm.loadTexture(d3d, L"../bin/data/BloonsMap.dds", "mainBackground");
	spr_bg.init(texName, { 0, 0, 1920, 1080 }, { 0, 0 }, 0, { 1, 1 });
	texName = rm.loadTexture(d3d, L"../bin/data/PlayIcon.dds", "playIcon");
	btn_play.init(d3d, rm, { 256, 256 }, texName, { 0, 0, 256, 256 }, { 1680, 744 }, 0, { 1, 1 });		
	texName = rm.loadTexture(d3d, L"../bin/data/ExitIcon.dds", "ExitIcon");
	btn_exit.init(d3d, rm, { 128, 128 }, texName, { 0, 0, 128, 128 }, { 84, 980 }, 0, { 1, 1 });
	// message bloons
	bloons.resize(23);
	for (int i(0); i < bloons.size(); i++) {
		bloons[i].init(rm, d3d, track, msgBloonProgress[i], string(1, loseMsg[i]));
	}
}
void StartMode::update(float dTime, Vector2 mousePos, bool isLMBPressed) {
	btn_play.update(dTime, mousePos, isLMBPressed);
	if (btn_play.getButton().getIsBtnDown())
		(*GameStats::GetInstance()).setMode(Modes::place);
	btn_exit.update(dTime, mousePos, isLMBPressed);
	if(btn_exit.getButton().getIsBtnDown())
		(*GameStats::GetInstance()).setMode(Modes::quit);
}
void StartMode::render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime) {
	spr_bg.render(d3d, rm, dTime, sprBatch);	
	for (int i(0); i < bloons.size(); i++) {
		bloons[i].render(rm, d3d, dTime, sprBatch);
	}
	btn_play.render(d3d, rm, dTime, sprBatch);
	btn_exit.render(d3d, rm, dTime, sprBatch);
}