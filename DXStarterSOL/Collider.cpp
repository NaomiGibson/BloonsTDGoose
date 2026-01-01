#include "Collider.h"
void Collider::init(ResourceManager& rm, MyD3D& d3d, Vector2 centre_, float rad_) {
	centre = centre_;
	db_spr.init(*(rm.findSpritesheet(rm.loadSpritesheet(d3d, L"../bin/data/CollisionRadius.dds", "collisionRad", 2, 1, 2))), 1, centre, 0, { 1, 1 });
	setRad(rad_);
	db_spr.setOrigin({ 0.5f, 0.5f });
}
void Collider::db_render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	db_spr.render(d3d, rm, dTime, batch);
}
void Collider::setPos(Vector2 pos_) {
	centre = pos_; 
	db_spr.setPos(pos_);
}
void Collider::setRad(float rad_) {
	rad = rad_;
	db_spr.setScale({ (rad * 2) / db_spr.GetScreenSize().x, (rad * 2) / db_spr.GetScreenSize().y });
}
float Collider::getDistance(const Collider& other) {
	return getDistance(other.centre);
}
float Collider::getDistance(Vector2 other) {
	float xDist = abs(centre.x - other.x);
	float yDist = abs(centre.y - other.y);
	return sqrt(xDist * xDist + yDist * yDist);

}
bool Collider::isColliding(const Collider& other) {
	float touchingDist = rad + other.rad;
	float dist = getDistance(other);
	return dist <= touchingDist;
}
bool Collider::isColliding(Vector2 other) {
	float dist = getDistance(other);
	return dist <= rad;
}
void Collider::onCollision(ResourceManager& rm, bool isColliding) {
	if (isColliding)
		db_spr.setTexRect(rm.findRect(db_spr.getTexName(), 2));
	else
		db_spr.setTexRect(rm.findRect(db_spr.getTexName(), 1));
}