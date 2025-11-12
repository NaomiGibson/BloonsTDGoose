#include "Goose.h"
void Goose::setRange(float radius) {
	range = radius;
	coll_range.setRad(radius);
}
void Goose::init(ResourceManager& rm, MyD3D& d3d, Vector2 pos) {
	spr.init(rm.loadSpritesheet(d3d, L"../bin/data/Geese.dds", "goose", 4, 4, 5), 1, pos, 0, { 1, 1 });
	range = 128;
	coll_range.init(rm, d3d, spr.getPos(), range);
	spr.setOrigin({ 0.5, 0.5 });
	coll_range.getDbSpr().setOrigin({ 0.5, 0.5 });
	isActive = true;
}
void Goose::update(float dTime, float timeScale, Bloons& bloons, Projectiles& projectiles) {
	findTarget(timeScale, bloons, projectiles);
}
void Goose::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	spr.render(d3d, rm, dTime, batch);
	coll_range.db_render(d3d, rm, dTime, batch);
}
void Goose::fire(float timeScale, Bloons& bloons, int idx, Projectiles& projectiles) {
	Vector2 tgt = bloons.getPos(idx);
	Vector2 vec_direction = { tgt.x - spr.getPos().x, tgt.y - spr.getPos().y};
	float direction = atan2(vec_direction.y, vec_direction.x);
	spr.setRotationRads(direction);
	projectiles.activate(spr.getPos(), direction);
}
bool Goose::findTarget(float timeScale, Bloons& bloons, Projectiles& projectiles) {
	static float lastShot = -shootSpeed;
	float time = GetClock();
	if (time - lastShot >= shootSpeed / timeScale) {					// at the set shoot speed
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
			fire(timeScale, bloons, closestIdx, projectiles);
			return true;
		}
	}
	return false;
}