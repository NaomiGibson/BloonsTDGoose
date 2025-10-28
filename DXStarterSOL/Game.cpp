#include "Game.h"

Game::Game(MyD3D* d3d_) 
:	p_d3d(d3d_)
{

}
void Game::init() {
	rm.loadFont(*p_d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	gpSpriteBatch = new SpriteBatch(&(*p_d3d).GetDeviceCtx());
	assert(gpSpriteBatch);

}
void Game::release() {
	rm.release();
}
void Game::update() {
}
void Game::render() {
	p_d3d->BeginRender({ 0, 0, 0, 1 });
	CommonStates dxstate(&(*p_d3d).GetDevice());
	gpSpriteBatch->Begin(SpriteSortMode_Deferred, dxstate.NonPremultiplied());

	spr_bg.render(*p_d3d, rm, 0, *gpSpriteBatch);

	gpSpriteBatch->End();
	p_d3d->EndRender();
}