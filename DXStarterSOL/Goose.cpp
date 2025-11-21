#include "Goose.h"
void Goose::init(ResourceManager& rm, MyD3D& d3d) {
	spr.init(rm.loadSpritesheet(d3d, L"../bin/data/Geese.dds", "goose", 4, 4, 5), 1, { 0, 0 }, 0, {1, 1});
	float range = 128;
	coll_range.init(rm, d3d, spr.getPos(), range);
	spr.setOrigin({ 0.42f, 0.5 });
	spr.setRotation(90);
	coll_range.getDbSpr().setOrigin({ 0.5, 0.5 });
	coll_goose.init(rm, d3d, spr.getPos() + spr.GetScreenSize() / 2, 24);
	spr_rangeIndicator.init(rm.loadSpritesheet(d3d, L"../bin/data/CollisionRadius.dds", "collisionRad", 2, 1, 2), 1, spr.getPos(), 0, {1, 1});
	spr_rangeIndicator.setOrigin({ 0.5f, 0.5f });
	spr_rangeIndicator.setIsActive(false);
	setRange(range);
	btn_selectGoose.init(rm, d3d, spr.getPos(), spr.GetScreenSize().x / 2);
}
void Goose::updateDefend(float dTime, Bloons& bloons, Projectiles& projectiles, Vector2 mousePos, bool isLMBPressed) {
	if (isActive) {
		findTarget(bloons, projectiles);
	}
}
void Goose::updatePlace(float dTime, Vector2 mousePos, bool isLMBPressed) {
	if (isActive) {
		btn_selectGoose.update(dTime, mousePos, isLMBPressed);
		if (!isSelected && btn_selectGoose.getIsHovered())
			spr_rangeIndicator.setIsActive(true);
		else if(!isSelected && !btn_selectGoose.getIsHovered())
			spr_rangeIndicator.setIsActive(false);
	}
}
void Goose::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	if (isActive) {
		//coll_goose.db_render(d3d, rm, dTime, batch);
		//coll_range.db_render(d3d, rm, dTime, batch);
		spr.render(d3d, rm, dTime, batch);
		spr_rangeIndicator.render(d3d, rm, dTime, batch);
	}
}
void Goose::setRange(float rad) {
	coll_range.setRad(rad);
	spr_rangeIndicator.setScale({ (rad * 2) / spr_rangeIndicator.getTexSize().x, (rad * 2) / spr_rangeIndicator.getTexSize().y });
}
void Goose::fire(Bloons& bloons, int idx, Projectiles& projectiles) {
	Vector2 tgt = bloons.getPos(idx);
	Vector2 vec_direction = { tgt.x - spr.getPos().x, tgt.y - spr.getPos().y};
	float direction = atan2(vec_direction.y, vec_direction.x);
	spr.setRotationRads(direction);
	projectiles.activate(spr.getPos(), direction, bulletDurability);
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
	btn_selectGoose.setPos(pos_);
	spr_rangeIndicator.setPos(pos_);

	appliedUpgrades.at(projectileReinforcement_1) = false;
	appliedUpgrades.at(projectileReinforcement_2) = false;
	appliedUpgrades.at(quickFire_1) = false;
	appliedUpgrades.at(quickFire_2) = false;
	appliedUpgrades.at(longDistance_1) = false;
	appliedUpgrades.at(longDistance_2) = false;
	setRange(128);
	bulletDurability = 1;
	shootSpeed = 2;

	isActive = true;
}
void Goose::select() {
	spr_rangeIndicator.setIsActive(true);
	isSelected = true;
}
void Goose::deselect() {
	spr_rangeIndicator.setIsActive(false);
	isSelected = false;
}
void Goose::applyUpgrade(ResourceManager& rm, upgrades upgrade) {
	if (upgrade != none) {
			appliedUpgrades.at(upgrade) = true;
		switch (upgrade)
		{
		case projectileReinforcement_1:
			bulletDurability = 2;
			break;
		case projectileReinforcement_2:
			bulletDurability = 3;
			break;
		case quickFire_1:
			shootSpeed = 1.f;
			break;
		case quickFire_2:
			shootSpeed = 0.5f;
			break;
		case longDistance_1:
			setRange(196);
			break;
		case longDistance_2:
			setRange(256);
			break;
		default:
			break;
		}
	}
}
void Goose::selectPurchasableUpgrades(upgrades& u1, upgrades& u2, upgrades& u3) {
	if (!appliedUpgrades.at(projectileReinforcement_1))
		u1 = projectileReinforcement_1;
	else if (!appliedUpgrades.at(projectileReinforcement_2))
		u1 = projectileReinforcement_2;
	else
		u1 = none;
	if (!appliedUpgrades.at(quickFire_1))
		u2 = quickFire_1;
	else if (!appliedUpgrades.at(quickFire_2))
		u2 = quickFire_2;
	else
		u2 = none;
	if (!appliedUpgrades.at(longDistance_1))
		u3 = longDistance_1;
	else if (!appliedUpgrades.at(longDistance_2))
		u3 = longDistance_2;
	else
		u3 = none;
}