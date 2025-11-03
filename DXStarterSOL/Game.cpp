#include "Game.h"

Game::Game(MyD3D* d3d_) 
:	p_d3d(d3d_), bloon(track) {
}
void Game::init() {
	rm.loadFont(*p_d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	spr_bg.init(rm.loadTexture(*p_d3d, L"../bin/data/BloonsMap.dds", "mainBackground"), { 0, 0, 1920, 1080 }, { 0, 0 }, 0, { 1, 1 });
	goose.init(rm, *p_d3d);
	bloon.init(rm, *p_d3d);

	gameStats.init(*p_d3d, rm, lives, 0, 1);

	gpSpriteBatch = new SpriteBatch(&(*p_d3d).GetDeviceCtx());
	assert(gpSpriteBatch);
}
void Game::release() {
	rm.release();
}
void Game::update(float dTime) {
	if (!bloon.update(dTime)) {
		lives--;
		gameStats.setLives(lives);
	}
}
void Game::render(float dTime) {
	p_d3d->BeginRender({ 0, 0, 0, 0 });
	CommonStates dxstate(&(*p_d3d).GetDevice());
	gpSpriteBatch->Begin(SpriteSortMode_Deferred, dxstate.NonPremultiplied());

	spr_bg.render(*p_d3d, rm, 0, *gpSpriteBatch);
	goose.render(*p_d3d, rm, 0, *gpSpriteBatch);
	bloon.render(*p_d3d, rm, 0, *gpSpriteBatch);
	gameStats.render(*p_d3d, rm, dTime, *gpSpriteBatch);

	gpSpriteBatch->End();
	p_d3d->EndRender();
}