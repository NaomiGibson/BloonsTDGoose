#include "GoosePlacer.h"

void GoosePlacer::init(ResourceManager& rm, MyD3D& d3d) {
	spr.init(rm.loadSpritesheet(d3d, L"../bin/data/Geese.dds", "goose", 4, 4, 5), 1, { 0, 0 }, 0, { 1, 1 });
	spr.setOrigin({ 0.5f, 0.5f });
}
void GoosePlacer::update(Vector2 mousePos, bool isLMBPressed, Goose geese[]) {
	if (isActive) {
		if (isLMBPressed) {
			spr.setPos(mousePos);
		}
		else  {
			placeGoose(mousePos, geese);
		}
	}
}
void GoosePlacer::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	if (isActive) {
		spr.render(d3d, rm, dTime, batch);
	}
}
void GoosePlacer::placeGoose(Vector2 pos, Goose geese[]) {
	for (int i(0); i < GC::MAX_GEESE; i++) {
		if (!geese[i].getIsActive()) {
			if ((*GameStats::GetInstance()).spendCoins(GC::GOOSE_COST)) {
				i = GC::MAX_GEESE;
				geese[i].activate(pos);
			}
		}
	}

	isActive = false;
}
void GoosePlacer::activate() {
	isActive = true;
}