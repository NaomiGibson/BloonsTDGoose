#include "Collider.h"
void Collider::init(ResourceManager& rm, MyD3D& d3d, Vector2 centre_, float rad_) {
	centre = centre_;
	rad = rad_;
	db_spr.init(rm.loadSpritesheet(d3d, L"../bin/data/CollisionRadius.dds", "collisionRad", 2, 1, 2), 1, centre, 0, { 1, 1 });
	db_spr.setScale({ (rad * 2) / db_spr.GetScreenSize().x, (rad * 2) / db_spr.GetScreenSize().y });
}
void Collider::db_render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	db_spr.render(d3d, rm, dTime, batch);
}
void Collider::setPos(Vector2 pos_) {
	centre = pos_; 
	db_spr.setPos(pos_);
}
bool Collider::isColliding(const Collider& other) {
	float xDist = abs(centre.x - other.centre.x);
	float yDist = abs(centre.y - other.centre.y);
	float dist = sqrt(xDist * xDist + yDist * yDist);
	float touchingDist = rad + other.rad;
	return dist <= touchingDist;
}
void Collider::onCollision(ResourceManager& rm) {
	db_spr.setTexRect(rm.findRect(db_spr.getTexName(), 2));
}