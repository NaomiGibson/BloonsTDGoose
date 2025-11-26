#include "Bloons.h"
void Bloons::init(ResourceManager& rm, MyD3D& d3d) {
	spr.init(rm.loadSpritesheet(d3d, L"../bin/data/Bloons.dds", "bloons", 2, 4, 5), 1, { 0, 0 }, 0, { 1, 1 });
	collider.init(rm, d3d, { 0, 0 }, 26);
	collider.getDbSpr().setOrigin({ 0.5f, 0.5f });
	spr.setOrigin({ 0.5, 0.5 });
	std::fill_n(speed, GC::MAX_BLOONS, 100);
	std::fill_n(value, GC::MAX_BLOONS, 1);
	rounds.resize(GC::MAX_ROUNDS);
	rounds = {
		{ // round 1
			{ 0, 1, 1.f, { 1 }},
		},
		{ // round 2
			{ 0, 5, 3.f, { 1 } },
		},
		{ // round 3
			{ 0, 2, 0.5f, { 1 } },
			{ 4, 2, 0.5f, { 1 } },
			{ 4, 2, 0.5f, { 1 } },
			{ 4, 2, 0.5f, { 1 } },
			{ 4, 2, 0.5f, { 1 } },
		},
		{ // round 4
			{ 0, 5, 2.1f, { 1 } },
			{ 4, 1, 0, { 2 } },
		},
		{ // round 5
			{ 0, 4, 2.1f, { 1, 2 } },
			{ 10, 4, 2.1f, { 1, 2 } },
		},
	};
}
Bloons::Wave& Bloons::getWave() {
	return rounds[currRound][currWave];
}
void Bloons::endWave() {
	currWave++;
	bloonsSpawned = 0;
	waveEndTime = GetClock();
}
void Bloons::endRound() {
	currRound++;
	currWave = 0;
	(*GameStats::GetInstance()).nextRound();
}
// Handles all bloon spawning logic
// @param idx must be that of an inactive bloon
void Bloons::spawnBloon(int idx) {
	assert(!isActive[idx]);
	static float lastBloonSpawn = -GC::BLOON_SPAWN_RATE;
	float time = GetClock();

	if (!isRoundFinished()) {																		// until all waves are complete
		if (time - waveEndTime >= rounds[currRound][currWave].wait / (*GameStats::GetInstance()).getTimeScale()) { // wait inbetween waves
			if (time - lastBloonSpawn >= getWave().spawnRate / (*GameStats::GetInstance()).getTimeScale()) {	// at the set bloon spawn rate
				if (bloonsSpawned < getWave().numBloons) {							// until all bloons for the wave have been spawned
					bloonsSpawned++;
					activate(idx, getWave().bloonHealth[bloonsSpawned % getWave().bloonHealth.size()]);		// activate an inactive bloon. idx must be that of an active bloon
					lastBloonSpawn = GetClock();
				}
				else {

					endWave();
				}
			}

		}
	}
}
bool Bloons::update(float dTime) {
	bool isLifeLost = false;
	for (int i(0); i < GC::MAX_BLOONS; i++) {
		if (isActive[i]) {
			progress[i] += speed[i] * dTime * (*GameStats::GetInstance()).getTimeScale();
			if (progress[i] > track.getProgressAtPoint(1) && progress[i] < track.getProgressAtPoint(4)) // determing the layer for bloons to appear under / over bridges
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
			spawnBloon(i);
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
			spr.setTexRect(rm.findRect("bloons", health[i]));
			spr.render(d3d, rm, dTime, batch);			
			//collider.setPos(pos);						// do the same for the collider debug sprite
			//collider.db_render(d3d, rm, dTime, batch);
		}
	}
}
void Bloons::reset() {
	bloonsSpawned = 0;
	for (int i(0); i < GC::MAX_BLOONS; i++) {
		isActive[i] = false;
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
bool Bloons::isRoundFinished() {
	return (currWave >= rounds[currRound].size());
}
bool Bloons::areAllRoundsFinished() {
	return currRound >= GC::MAX_ROUNDS;
}
void Bloons::setHealth(int idx, int health_) {
	health[idx] = health_;
	if (health[idx] == 0) {
		isActive[idx] = false;
	}
}
void Bloons::activate(int idx, int health_) {
	isActive[idx] = true;
	progress[idx] = 0;
	setHealth(idx, health_);
}
Collider& Bloons::getCollider(int idx) {
	collider.setPos(position[idx]);
	return collider;
}
void Bloons::onCollision_projectile(int idx) {
	(*GameStats::GetInstance()).addCoins(value[idx]);
	setHealth(idx, health[idx] - 1);
}