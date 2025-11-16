#include "Goose.h"
void Goose::setRange(float radius) {
	range = radius;
	coll_range.setRad(radius);
}
void Goose::init(ResourceManager& rm, MyD3D& d3d) {
	spr.init(rm.loadSpritesheet(d3d, L"../bin/data/Geese.dds", "goose", 4, 4, 5), 1, { 0, 0 }, 0, {1, 1});
	range = 128;
	coll_range.init(rm, d3d, spr.getPos(), range);
	spr.setOrigin({ 0.42, 0.5 });
	spr.setRotation(90);
	coll_range.getDbSpr().setOrigin({ 0.5, 0.5 });
	coll_goose.init(rm, d3d, spr.getPos() + spr.GetScreenSize() / 2, 24);
}
void Goose::update(float dTime, Bloons& bloons, Projectiles& projectiles) {
	if (isActive) {
		findTarget(bloons, projectiles);
	}
}
void Goose::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	if (isActive) {
		spr.render(d3d, rm, dTime, batch);
		coll_range.db_render(d3d, rm, dTime, batch);
		//coll_goose.db_render(d3d, rm, dTime, batch);
	}
}
void Goose::fire(Bloons& bloons, int idx, Projectiles& projectiles) {
	Vector2 tgt = bloons.getPos(idx);
	Vector2 vec_direction = { tgt.x - spr.getPos().x, tgt.y - spr.getPos().y};
	float direction = atan2(vec_direction.y, vec_direction.x);
	spr.setRotationRads(direction);
	projectiles.activate(spr.getPos(), direction);
}
bool Goose::findTarget(Bloons& bloons, Projectiles& projectiles) {
	float time = GetClock();
	if (time - lastShot >= shootSpeed / (*GameStats::GetInstance()).getTimeScale()) {					// at the set shoot speed
		int closestIdx(0);
		float closestDist(coll_range.getDistance(bloons.getCollider(0)));
		float thisDist(closestDist);
		for (int i(1); i < GC::MAX_BLOONS; i++) {						// find the closest bloon
			if (bloons.getIsActive(i)) {
				thisDist = coll_range.getDistance(bloons.getCollider(i));
				if (thisDist < closestDist) {
					closestDist = thisDist;
					closestIdx = i;
				}
			}
		}
		if (bloons.getIsActive(closestIdx) && coll_range.isColliding(bloons.getCollider(closestIdx))) {	// if the closest bloon is within range, shoot it
			lastShot = time;
			fire(bloons, closestIdx, projectiles);
			return true;
		}
	}
	return false;
}
void Goose::activate(Vector2 pos_) {
	spr.setRotation(90);
	spr.setPos(pos_);
	coll_range.setPos(pos_);
	coll_goose.setPos(pos_);
	isActive = true;
}