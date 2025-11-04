#include "Game.h"

Game::Game(MyD3D* d3d_) 
:	p_d3d(d3d_) {
}
void Game::release() {
	rm.release();
}
void Game::init() {
	gpSpriteBatch = new SpriteBatch(&(*p_d3d).GetDeviceCtx());
	assert(gpSpriteBatch);
}
void Game::update(float dTime) { 
	Modes oldMode = mode;
	switch (mode)
	{
	case start: // return isStartPressed
		break;
	case place: // return isStartPressed
		break;
	case defend:  // return gameStats and use that to determine change of state?
		oldMode = defendMode.update(dTime);
		break;
	case win:					// return buttonPressed ~~ probably not :/
		break;
	case lose:				// return buttonPressed?
		oldMode = loseMode.update(dTime);
		break;
	default:
		break;
	}
	if (mode != oldMode) {
		changeState(oldMode);
	}
}
void Game::render(float dTime) {
	switch (mode)
	{
	case start:
		break;
	case place:
		break;
	case defend:
		defendMode.render(rm, *p_d3d, *gpSpriteBatch, dTime);
		break;
	case win:
		break;
	case lose:
		loseMode.render(rm, *p_d3d, *gpSpriteBatch, dTime);
		break;
	default:
		break;
	}
}
void Game::changeState(Modes oldMode) {
	switch (oldMode)
	{
	case start:
		break;
	case place:
		break;
	case defend:
		defendMode.release();
		break;
	case win:
		break;
	case lose:
		loseMode.release();
		break;
	default:
		break;
	}
	switch (mode)
	{
	case start:
		break;
	case place:
		break;
	case defend:
		defendMode.init(rm, *p_d3d);
		break;
	case win:
		break;
	case lose:
		loseMode.init(rm, *p_d3d);
		break;
	default:
		break;
	}
}