#include "Projectiles.h"

void Projectiles::init(ResourceManager& rm, MyD3D& d3d) {
	spr.init(rm.loadTexture(d3d, L"../bin/data/Projectile.dds", "projectile"), {0, 0, 8, 8}, {0, 0}, 0, {1, 1});
	collider.init(rm, d3d, { 0, 0 }, 4);
	collider.getDbSpr().setOrigin({ 0.5, 0.5 });
	spr.setOrigin({ 0.5, 0.5 });
	std::fill_n(speed, GC::MAX_PROJECTILES, 3000);
	std::fill_n(health, GC::MAX_PROJECTILES, 1);
	std::fill_n(bloonHit, GC::MAX_PROJECTILES, -1);
}
void Projectiles::update(float dTime) {
	for (int i(0); i < GC::MAX_PROJECTILES; i++) {
		if (position[i].x > 0 &&
		position[i].x < WinUtil::Get().GetData().clientWidth &&
		position[i].y > 0 &&
		position[i].y < WinUtil::Get().GetData().clientHeight) 
		{
			position[i] += direction[i] * speed[i] * dTime;
		}
		else
			isActive[i] = false;
	}
}
void Projectiles::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	for (int i(0); i < GC::MAX_PROJECTILES; i++) {
		if (isActive[i]) {
			spr.setPos(position[i]);
			spr.render(d3d, rm, dTime, batch);
			collider.setPos(position[i]);
			collider.db_render(d3d, rm, dTime, batch);
		}
	}
}
void Projectiles::activate(Vector2 startPos, float directionRads, int health_) {
	for (int i(0); i < GC::MAX_PROJECTILES; i++) {
		if (!isActive[i]) {
			isActive[i] = true;
			position[i] = startPos;
			direction[i] = { (float)cos(directionRads), (float)sin(directionRads) };
			health[i] = health_;
			bloonHit[i] == -1;
			i = GC::MAX_PROJECTILES;
		}
	}
}
Collider& Projectiles::getCollider(int idx) {
	collider.setPos(position[idx]);
	return collider;
}
void Projectiles::onCollision_bloon(int idx, int bloonIdx) {
	health[idx]--;
	if (health[idx] == 0) {
		bloonHit[idx] = -1;
		isActive[idx] = false;
	}
	else
		bloonHit[idx] = bloonIdx;
}