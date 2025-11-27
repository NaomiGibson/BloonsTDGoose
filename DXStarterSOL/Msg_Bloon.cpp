#include "Msg_Bloon.h"

void Msg_Bloon::init(ResourceManager& rm, MyD3D& d3d, Track& track, float progress, string letter) {
	pos = track.findPos(progress);
	spr.init(rm.loadSpritesheet(d3d, L"../bin/data/Bloons.dds", "bloons", 2, 4, 5), 1, { 0, 0 }, 0, { 1, 1 });
	rm.loadFont(d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	spr.setOrigin({ 0.5f, 0.5f });
	spr.setPos(pos);
	txt.setOrigin({ 0.5f, 0.5f });
	txt.setPos(pos - Vector2{ 12, 18 });
	txt.setMsg(letter);
}
void Msg_Bloon::update() {

}
void Msg_Bloon::render(ResourceManager& rm, MyD3D& d3d, float dTime, SpriteBatch& batch) {
	spr.render(d3d, rm, dTime, batch);
	txt.render(d3d, rm, dTime, batch);
}