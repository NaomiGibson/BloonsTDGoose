#include "Msg_Bloon.h"

void Msg_Bloon::init(ResourceManager& rm, MyD3D& d3d, Track& track, float progress, string letter, int health) {
	pos = track.findPos(progress);
	spr.init(*(rm.findSpritesheet(rm.loadSpritesheet(d3d, L"../bin/data/Bloons.dds", "bloons", 2, 4, 5))), health, {0, 0}, 0, {1, 1});
	rm.loadFont(d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	spr.setOrigin({ 0.5f, 0.5f });
	txt.setOrigin({ 0.5f, 0.5f });
	txt.setPos(pos - Vector2{ 12, 18 });
	txt.setMsg(letter);
	hoverOffset = rand() % 360;	
	spr.setPos({ pos.x, pos.y + sin(hoverOffset) * hoverHeight });
}
void Msg_Bloon::update(float dTime) {
	hoverOffset = fmod(hoverOffset + dTime * speed, 360.f);
	Vector2 hoverPos = { pos.x, pos.y + sin(hoverOffset) * hoverHeight };
	spr.setPos(hoverPos);
	txt.setPos(hoverPos - Vector2{ 12, 18 });
}
void Msg_Bloon::render(ResourceManager& rm, MyD3D& d3d, float dTime, SpriteBatch& batch) {
	spr.render(d3d, rm, dTime, batch);
	txt.render(d3d, rm, dTime, batch);
}