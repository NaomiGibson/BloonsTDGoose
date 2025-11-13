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
void Bloons::spawnBloon(float timeScale, int idx) {
	assert(!isActive[idx]);
	static float lastBloonSpawn = -GC::BLOON_SPAWN_RATE;
	float time = GetClock();
	if (time - lastBloonSpawn >= GC::BLOON_SPAWN_RATE / timeScale) {			// at the set bloon spawn rate
		if (bloonsSpawned < GC::BLOONS_PER_ROUND) {					// until all bloons for the round have been spawned
			bloonsSpawned++;
			activate(idx);											// activate an inactive bloon. idx must be that of an active bloon
			lastBloonSpawn = GetClock();
		}
	}
}
bool Bloons::update(float dTime, float timeScale) {
	bool isLifeLost = false;
	for (int i(0); i < GC::MAX_BLOONS; i++) {
		if (isActive[i]) {
			progress[i] += speed[i] * dTime;
			if (progress[i] > track.getProgressAtPoint(1) && progress[i] < track.getProgressAtPoint(4)) // determing the layer for bloons that appear under / over bridges
				layer[i] = 0;
			else if (progress[i] > track.getProgressAtPoint(4) && progress[i] < track.getProgressAtPoint(13))
				layer[i] = 1;
			else
				layer[i] = 2;
			if (progress[i] > track.getLength()) {	// if bloon has reached the end of the track
				isActive[i] = false;				// deactivate it and lose a life
				(*GameStats::GetInstance()).loseLife();
				isLifeLost = true;
			}
		}
		else {
			spawnBloon(timeScale, i);
		}
	}
	return isLifeLost;
}
void Bloons::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch, int layer_) {
	for (int i(0); i < GC::MAX_BLOONS; i++) {
		if (isActive[i] && layer[i] == layer_) {
			Vector2 pos = track.findPos(progress[i]);	// set sprite position to the
			position[i] = pos;							// position of the bloon and 
			spr.setPos(pos);							// render it for each bloon
			spr.render(d3d, rm, dTime, batch);			
			collider.setPos(pos);						// do the same for the collider debug sprite
			collider.db_render(d3d, rm, dTime, batch);
		}
	}
}
void Bloons::reset() {
	bloonsSpawned = 0;
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
	(*GameStats::GetInstance()).addCoins(value[idx]);
	isActive[idx] = false;
}