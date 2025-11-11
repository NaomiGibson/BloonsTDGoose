#include "Game.h"

Game::Game(MyD3D* d3d_) 
:	p_d3d(d3d_) {
}
void Game::release() {
	rm.release();
}

void Game::init() {
	switch (mode)
	{
	case start:
		startMode.init(rm, *p_d3d);
		break;
	case place:
		placeMode.init(rm, *p_d3d);
		break;
	case defend:
		defendMode.init(rm, *p_d3d);
		break;
	case win:
		winMode.init(rm, *p_d3d);
		break;
	case lose:
		loseMode.init(rm, *p_d3d);
		break;
	default:
		break;
	}
	gpSpriteBatch = new SpriteBatch(&(*p_d3d).GetDeviceCtx());
	assert(gpSpriteBatch);
}
void Game::update(float dTime, Vector2 mousePos, bool isLMBPressed) {
	Modes oldMode = mode;
	switch (mode)
	{
	case start:
		mode = startMode.update(dTime * timeScale, mousePos, isLMBPressed);
		break;
	case place:
		mode = placeMode.update(dTime * timeScale, mousePos, isLMBPressed);
		break;
	case defend:
		mode = defendMode.update(rm, dTime * timeScale);
		break;
	case win:
		mode = winMode.update(dTime * timeScale, mousePos, isLMBPressed);
		break;
	case lose:
		mode = loseMode.update(dTime * timeScale, mousePos, isLMBPressed);
		break;
	default:
		break;
	}
	if (mode != oldMode) {
		changeState();
	}
}
void Game::render(float dTime) {
	p_d3d->BeginRender({ 0, 0, 0, 0 });
	CommonStates dxstate(&(*p_d3d).GetDevice());
	gpSpriteBatch->Begin(SpriteSortMode_Deferred, dxstate.NonPremultiplied());

	switch (mode)
	{
	case start:
		startMode.render(rm, *p_d3d, *gpSpriteBatch, dTime);
		break;
	case place:
		placeMode.render(rm, *p_d3d, *gpSpriteBatch, dTime);
		break;
	case defend:
		defendMode.render(rm, *p_d3d, *gpSpriteBatch, dTime);
		break;
	case win:
		winMode.render(rm, *p_d3d, *gpSpriteBatch, dTime);
		break;
	case lose:
		loseMode.render(rm, *p_d3d, *gpSpriteBatch, dTime);
		break;
	default:
		break;
	}
	gpSpriteBatch->End();
	p_d3d->EndRender();
}
void Game::changeState() {
	switch (mode)
	{
	case start:
		startMode.init(rm, *p_d3d);
		break;
	case place:
		placeMode.init(rm, *p_d3d);
		break;
	case defend:
		defendMode.init(rm, *p_d3d);
		break;
	case win:
		winMode.init(rm, *p_d3d);
		break;
	case lose:
		loseMode.init(rm, *p_d3d);
		break;
	default:
		break;
	}
}
