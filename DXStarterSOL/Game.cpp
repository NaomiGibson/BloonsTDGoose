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
		break;
	case place:
		break;
	case defend:defendMode.init(rm, *p_d3d);
		break;
	case win:
		break;
	case lose:
		break;
	default:
		break;
	}
	gpSpriteBatch = new SpriteBatch(&(*p_d3d).GetDeviceCtx());
	assert(gpSpriteBatch);
}
void Game::update(float dTime) { 
	Modes oldMode = mode;
	switch (mode)
	{
	case start:
		break;
	case place:
		break;
	case defend:
		mode = defendMode.update(dTime);
		break;
	case win:
		break;
	case lose:
		//mode = loseMode.update(dTime);
		break;
	default:
		break;
	}
	if (mode != oldMode) {
		changeState();
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
		//loseMode.render(rm, *p_d3d, *gpSpriteBatch, dTime);
		break;
	default:
		break;
	}
}
void Game::changeState() {
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
		//loseMode.init(rm, *p_d3d);
		break;
	default:
		break;
	}
}
