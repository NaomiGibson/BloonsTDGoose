#include "Goose.h"
void Goose::setRange(float radius) {
	radius;
	float spriteRadius = 256;
	float scale = radius / spriteRadius;
	spr_range.setScale({ scale, scale });
}
void Goose::init(ResourceManager& rm, MyD3D& d3d) {
	spr.init(rm.loadSpritesheet(d3d, L"../bin/data/Geese.dds", "goose", 4, 4, 5), 1, { 528, 164 }, 0, { 1, 1 });
	spr_range.init(rm.loadTexture(d3d, L"../bin/data/GooseRadius.dds", "goose_rad"), {0, 0, 512, 512}, {528, 164}, 0, {1, 1});
	spr.setOrigin({ 0.5, 0.5 });
	spr_range.setOrigin({ 0.5, 0.5 });
	setRange(144);
	isActive = true;
}
void Goose::update(float dTime) {
	//if(spr.isColliding(spr.getPos, ))
}
void Goose::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	spr.render(d3d, rm, dTime, batch);
	spr_range.render(d3d, rm, dTime, batch);
}