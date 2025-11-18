#include "StartMode.h"
void StartMode::init(ResourceManager& rm, MyD3D& d3d) {
	rm.loadFont(d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	string texName = rm.loadTexture(d3d, L"../bin/data/BloonsMap.dds", "mainBackground");
	spr_bg.init(texName, { 0, 0, 1920, 1080 }, { 0, 0 }, 0, { 1, 1 });
	txt_title =  Text("Moghul", "BLOONS TD GEESE!", { 512, 512 }, { 0, 0, 0, 1 });
	texName = rm.loadTexture(d3d, L"../bin/data/PlayIcon.dds", "playIcon");
	btn_play.init(d3d, rm, { 256, 256 }, texName, { 0, 0, 256, 256 }, { 1680, 744 }, 0, { 1, 1 });
}
void StartMode::update(float dTime, Vector2 mousePos, bool isLMBPressed) {
	btn_play.update(dTime, mousePos, isLMBPressed);
	if (btn_play.getIsBtnDown())
		(*GameStats::GetInstance()).setMode(Modes::place);
}
void StartMode::render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime) {
	spr_bg.render(d3d, rm, dTime, sprBatch);
	txt_title.render(d3d, rm, dTime, sprBatch);
	btn_play.render(d3d, rm, dTime, sprBatch);
}