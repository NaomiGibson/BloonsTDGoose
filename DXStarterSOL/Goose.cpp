#include "Goose.h"
void Goose::setRange(float radius) {
	range = radius;
	coll_range.setRad(radius);
}
void Goose::init(ResourceManager& rm, MyD3D& d3d) {
	spr.init(rm.loadSpritesheet(d3d, L"../bin/data/Geese.dds", "goose", 4, 4, 5), 1, { 528, 260 }, 0, { 1, 1 });
	range = 128;
	coll_range.init(rm, d3d, spr.getPos(), range);
	spr.setOrigin({ 0.5, 0.5 });
	coll_range.getDbSpr().setOrigin({ 0.5, 0.5 });
	isActive = true;
}
void Goose::update(float dTime, Bloons& bloons, Projectiles& projectiles) {
	shoot(bloons, projectiles);
}
void Goose::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	spr.render(d3d, rm, dTime, batch);
	coll_range.db_render(d3d, rm, dTime, batch);
}
void Goose::fire(Bloons& bloons, int idx, Projectiles& projectiles) {
	Vector2 tgt = bloons.getPos(idx);
	float direction = atan2(abs(bloons.getPos(idx).x - spr.getPos().x), abs(bloons.getPos(idx).y - spr.getPos().y));
	spr.setRotationRads(direction);
	projectiles.activate(spr.getPos(), direction);
}
bool Goose::shoot(Bloons& bloons, Projectiles& projectiles) {
	static float lastShot = -shootSpeed;
	float time = GetClock();
	if (time - lastShot >= shootSpeed) {								// at the set shoot speed
		int closestIdx(0);
		float closestDist(coll_range.getDistance(bloons.getCollider(0)));
		float thisDist(closestDist);
		for (int i(1); i < GC::MAX_BLOONS; i++) {						// find the closest bloon
			thisDist = coll_range.getDistance(bloons.getCollider(i));
			if (thisDist < closestDist) {
				closestDist = thisDist;
				closestIdx = i;
			}
		}
		if (coll_range.isColliding(bloons.getCollider(closestIdx))) {	// if the closest bloon is within range, shoot it
			lastShot = time;
			fire(bloons, closestIdx, projectiles);
			return true;
		}
	}
	return false;
}