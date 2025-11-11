#include "GoosePlacer.h"

void GoosePlacer::init(ResourceManager& rm, MyD3D& d3d) {
	spr.init(rm.loadSpritesheet(d3d, L"../bin/data/Geese.dds", "goose", 4, 4, 5), 1, { 0, 0 }, 0, { 1, 1 });
	spr.setOrigin({ 0.5f, 0.5f });
}
void GoosePlacer::update(Vector2 mousePos, bool isLMBPressed) {
	if (isActive && isLMBPressed) {
		spr.setPos(mousePos);
	}
	else {
		placeGoose(mousePos);
	}
}
void GoosePlacer::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	if (isActive) {
		spr.render(d3d, rm, dTime, batch);
	}
}
void GoosePlacer::placeGoose(Vector2 pos) {
	isActive = false;
	//gameStats lose money
}