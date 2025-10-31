#include "Game.h"

Game::Game(MyD3D* d3d_) 
:	p_d3d(d3d_)
{

}
void Game::init() {
	rm.loadFont(*p_d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	spr_bg.init(rm.loadTexture(*p_d3d, L"../bin/data/BloonsMap.dds", "mainBackground"), { 0, 0, 1920, 1080 }, { 0, 0 }, 0, { 1, 1 });
	spr_goose.init(rm.loadSpritesheet(*p_d3d, L"../bin/data/Geese.dds", "Geese", 4, 4, 15), 14, { 200, 200 }, 0, { 3, 3 });
	spr_bloon.init(rm.loadSpritesheet(*p_d3d, L"../bin/data/Bloons.dds", "Bloons", 2, 4, 5), 1, { 300, 200 }, 0, { 3, 3 });

	gpSpriteBatch = new SpriteBatch(&(*p_d3d).GetDeviceCtx());
	assert(gpSpriteBatch);
}
void Game::release() {
	rm.release();
}
void Game::update() {
}
void Game::render() {
	p_d3d->BeginRender({ 0, 0, 0, 0 });
	CommonStates dxstate(&(*p_d3d).GetDevice());
	gpSpriteBatch->Begin(SpriteSortMode_Deferred, dxstate.NonPremultiplied());

	spr_bg.render(*p_d3d, rm, 0, *gpSpriteBatch);
	spr_goose.render(*p_d3d, rm, 0, *gpSpriteBatch);
	spr_bloon.render(*p_d3d, rm, 0, *gpSpriteBatch);

	gpSpriteBatch->End();
	p_d3d->EndRender();
}