#include "Bloons.h"
void Bloons::init(ResourceManager& rm, MyD3D& d3d) {
	spr.init(rm.loadSpritesheet(d3d, L"../bin/data/Bloons.dds", "bloons", 2, 4, 5), 1, { 0, 0 }, 0, { 1, 1 });
	collider.init(rm, d3d, { 0, 0 }, 26);
	collider.getDbSpr().setOrigin({ 0.5f, 0.58f });
	spr.setOrigin({ 0.5, 0.5 });
	std::fill_n(speed, GC::MAX_BLOONS, 100);
	std::fill_n(value, GC::MAX_BLOONS, 1);
}
// Handles all bloon spawning logic
// @param idx must be that of an inactive bloon
// @return true if a bloon spawned
void Bloons::spawnBloon(int idx) {
	assert(!isActive[idx]);
	static float lastBloonSpawn = -GC::BLOON_SPAWN_RATE;
	float time = GetClock();
	if (time - lastBloonSpawn >= GC::BLOON_SPAWN_RATE) {			// at the set bloon spawn rate
		if (bloonsSpawned < GC::BLOONS_PER_ROUND) {					// until all bloons for the round have been spawned
			bloonsSpawned++;
			activate(idx);											// activate an inactive bloon
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
int Bloons::getNumActiveBloons() {
	int count(0);
	for (int i(0); i < GC::MAX_BLOONS; i++) {
		if (isActive[i])
			count++;
	}
	return count;
}
void Bloons::activate(int idx) {
	isActive[idx] = true;
	progress[idx] = 0;
}
Collider& Bloons::getCollider(int idx) {
	collider.setPos(position[idx]);
	return collider;
}
void Bloons::onCollision_projectile(int idx) {
	gameStats.addCoins(value[idx]);
	isActive[idx] = false;
}