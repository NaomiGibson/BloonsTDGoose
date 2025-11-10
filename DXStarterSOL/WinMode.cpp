#include "WinMode.h"

void WinMode::init(ResourceManager& rm, MyD3D& d3d) {
	rm.loadFont(d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	string texName = rm.loadTexture(d3d, L"../bin/data/BloonsMap.dds", "mainBackground");
	spr_bg.init(texName, { 0, 0, 1920, 1080 }, { 0, 0 }, 0, { 1, 1 });
	txt_winMsg = Text("Moghul", "YOU WIN!", { 512, 512 }, { 0, 0, 0, 1 });
}
Modes WinMode::update(float dTime) {
	return win;
}
void WinMode::render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime) {
	spr_bg.render(d3d, rm, dTime, sprBatch);
	txt_winMsg.render(d3d, rm, dTime, sprBatch);
}