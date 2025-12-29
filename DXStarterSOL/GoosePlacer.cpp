#include "GoosePlacer.h"

void GoosePlacer::init(ResourceManager& rm, MyD3D& d3d) {
	spr.init(rm.findSpritesheet(rm.loadSpritesheet(d3d, L"../bin/data/Geese.dds", "goose", 4, 4, 5)), 1, { 0, 0 }, 90, { 1, 1 });
	spr.setOrigin({ 0.42f, 0.5 });
	collider.init(rm, d3d, spr.getPos() + spr.GetScreenSize() / 2, 24);
}
void GoosePlacer::update(ResourceManager& rm, Vector2 mousePos, bool isLMBPressed, Goose geese[], Track& track, Stats& ui_stats) {
	if (isActive) {
		if (isLMBPressed) {
			spr.setPos(mousePos);
		}
		else  {
			placeGoose(rm, mousePos, geese, track, ui_stats);
		}
		collider.setPos({ mousePos });
		collider.onCollision(rm, track.isOverlappingSection(collider.getCentre(), collider.getRad()));
	}
}
void GoosePlacer::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	if (isActive) {
		spr.render(d3d, rm, dTime, batch);
		//collider.db_render(d3d, rm, dTime, batch);
	}
}
void GoosePlacer::placeGoose(ResourceManager& rm, Vector2 pos, Goose geese[], Track& track, Stats& ui_stats) {
	bool canPlace = true;
	if (track.isOverlappingSection(pos, collider.getRad()))
		canPlace = false;
	for (int i(0); i < GC::MAX_GEESE; i++) {
		if (geese[i].getIsActive() && collider.isColliding(geese[i].getGooseCollider()))
			canPlace = false;
	}
	if (canPlace) {
		for (int i(0); i < GC::MAX_GEESE; i++) {
			if (!geese[i].getIsActive()) {
				if ((*GameStats::GetInstance()).spendCoins(GC::GOOSE_COST)) {
					geese[i].activate(rm, pos);
				}
				ui_stats.setCoins((*GameStats::GetInstance()).getCoins());
				break;
			}
		}
	}
	isActive = false;
}
void GoosePlacer::activate() {
	isActive = true;
}