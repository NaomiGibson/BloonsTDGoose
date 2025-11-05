#include "Bloon.h"
void Bloon::init(ResourceManager& rm, MyD3D& d3d) {
	spr.init(rm.loadSpritesheet(d3d, L"../bin/data/Bloons.dds", "bloons", 2, 4, 5), 1, { 0, 0 }, 0, { 1, 1 });
	spr.setOrigin({ 0.5, 0.5 });
}
bool Bloon::update(float dTime) {
	if (isActive) {
		progress += speed * dTime;
		if (progress < track.getLength()) {
			spr.setPos(track.findPos(progress));
			return true;
		}
		else {
			isActive = false;
			return false;
		}
	}
	return true;
}
void Bloon::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	if (isActive) {
		spr.render(d3d, rm, dTime, batch);
	}
}
void Bloon::activate() {
	isActive = true;
	progress = 0;
}