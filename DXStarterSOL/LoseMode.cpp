#include "LoseMode.h"

void LoseMode::init(ResourceManager& rm, MyD3D& d3d) {
	rm.loadFont(d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	string texName = rm.loadTexture(d3d, L"../bin/data/BloonsMap.dds", "mainBackground");
	spr_bg.init(texName, { 0, 0, 1920, 1080 }, { 0, 0 }, 0, { 1, 1 });
	txt_loseMsg = Text("Moghul", "YOU LOSE!", { 512, 512 }, { 0, 0, 0, 1 });
}
Modes LoseMode::update(float dTime) {
	for (int i = 0; i < 7; i++) {
		//spr_bloons[i].update(dTime);
	}
	return Modes::lose;
}
void LoseMode::render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime) {
	spr_bg.render(d3d, rm, dTime, sprBatch);
	txt_loseMsg.render(d3d, rm, dTime, sprBatch);
	//for (int i = 0; i < 7; i++) {
	//	spr_bloons[i].render(d3d, rm, dTime, sprBatch);
	//	txt_loseMsgs[i].render(d3d, rm, dTime, sprBatch);
	//}
}