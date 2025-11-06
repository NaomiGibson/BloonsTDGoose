#include "LoseMode.h"

void LoseMode::init(ResourceManager& rm, MyD3D& d3d) {
	rm.loadFont(d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	string texName = rm.loadTexture(d3d, L"../bin/data/BloonsMap.dds", "mainBackground");
	spr_bg.init(texName, { 0, 0, 1920, 1080 }, { 0, 0 }, 0, { 1, 1 });
	//txt_loseMsg = Text("Moghul", "YOU LOSE!", {512, 512}, {0, 0, 0, 0});
	//for (int i = 0; i < 7; i++) {
	//	spr_bloons.push_back(Sprite());
	//	spr_bloons[i].init(rm.loadSpritesheet(d3d, L"../bin/data/Bloons.dds", "bloons", 2, 4, 5), 1, { 0, 0 }, 0, { 1, 1 });
	//	spr_bloons[i].setOrigin({ 0.5, 0.5 });
	//}
	//txt_loseMsgs.push_back(Text("Moghul", "Y"));
	//txt_loseMsgs.push_back(Text("Moghul", "O"));
	//txt_loseMsgs.push_back(Text("Moghul", "U"));
	//txt_loseMsgs.push_back(Text("Moghul", "L"));
	//txt_loseMsgs.push_back(Text("Moghul", "O"));
	//txt_loseMsgs.push_back(Text("Moghul", "S"));
	//txt_loseMsgs.push_back(Text("Moghul", "E"));
	//txt_loseMsgs[1].setMsg("O");
	//txt_loseMsgs[2].setMsg("U");
	//txt_loseMsgs[3].setMsg("L");
	//txt_loseMsgs[4].setMsg("O");
	//txt_loseMsgs[5].setMsg("S");
	//txt_loseMsgs[6].setMsg("E");
	//spr_bloons[0].setPos({ 260, 360 });
	//spr_bloons[1].setPos({ 340, 360 });
	//spr_bloons[2].setPos({ 420, 360 });
	//spr_bloons[3].setPos({ 750, 552 });
	//spr_bloons[4].setPos({ 830, 552 });
	//spr_bloons[5].setPos({ 910, 552 });
	//spr_bloons[6].setPos({ 990, 552 });
	//txt_loseMsgs[0].setPos({ 260, 360 });
	//txt_loseMsgs[1].setPos({ 340, 360 });
	//txt_loseMsgs[2].setPos({ 420, 360 });
	//txt_loseMsgs[3].setPos({ 750, 552 });
	//txt_loseMsgs[4].setPos({ 830, 552 });
	//txt_loseMsgs[5].setPos({ 910, 552 });
	//txt_loseMsgs[6].setPos({ 990, 552 });

}
Modes LoseMode::update(float dTime) {
	for (int i = 0; i < 7; i++) {
		//spr_bloons[i].update(dTime);
	}
	return Modes::lose;
}
void LoseMode::render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime) {
	spr_bg.render(d3d, rm, dTime, sprBatch);
	//txt_loseMsg.render(d3d, rm, dTime, sprBatch);
	//for (int i = 0; i < 7; i++) {
	//	spr_bloons[i].render(d3d, rm, dTime, sprBatch);
	//	txt_loseMsgs[i].render(d3d, rm, dTime, sprBatch);
	//}
}