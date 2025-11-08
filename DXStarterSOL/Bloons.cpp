#include "Bloons.h"
void Bloons::init(ResourceManager& rm, MyD3D& d3d) {
	spr.init(rm.loadSpritesheet(d3d, L"../bin/data/Bloons.dds", "bloons", 2, 4, 5), 1, { 0, 0 }, 0, { 1, 1 });
	collider.init(rm, d3d, { 0, 0 }, 26);
	collider.getDbSpr().setOrigin({ 0.5, 0.58 });
	spr.setOrigin({ 0.5, 0.5 });
	std::fill_n(speed, GC::MAX_BLOONS, 100);
}
// Handles all bloon spawning logic
// @return true if a bloon spawned
void Bloons::spawnBloon(int idx) {
	static float lastBloonSpawn = 0;
	float time = GetClock();
	if (time - lastBloonSpawn > GC::BLOON_SPAWN_RATE) {			// at the set bloon spawn rate
		if (!isActive[idx]) {						// search for an inactive bloon
			activate(idx);							// and activate it
			lastBloonSpawn = GetClock();
		}
	}
}
bool Bloons::update(float dTime) {
	bool isLifeLost = false;
	for (int i(0); i < GC::MAX_BLOONS; i++) {
		if (isActive[i]) {
			progress[i] += speed[i] * dTime;
			if (progress[i] > track.getLength()) {	// if bloon has reached the end of the track
				isActive[i] = false;				// deactivate it and lose a life
				gameStats.loseLife();
				isLifeLost = true;
			}
		}
		else {
			spawnBloon(i);
		}
	}
	return isLifeLost;
}
void Bloons::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	for (int i(0); i < GC::MAX_BLOONS; i++) {
		if (isActive[i]) {
			Vector2 pos = track.findPos(progress[i]);
			position[i] = pos;
			spr.setPos(pos);
			spr.render(d3d, rm, dTime, batch);
			collider.setPos(pos);
			collider.db_render(d3d, rm, dTime, batch);
		}
	}
}
void Bloons::activate(int idx) {
	isActive[idx] = true;
	progress[idx] = 0;
}
Collider& Bloons::getCollider(int idx) {
	collider.setPos(position[idx]);
	return collider;
}