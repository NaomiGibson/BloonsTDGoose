#include "Game.h"

Game::Game(MyD3D* d3d_) 
:	p_d3d(d3d_) {
}
void Game::release() {
	rm.release();
}

void Game::init() {
	track.init(rm, *p_d3d);
	bloons.init(rm, *p_d3d);
	for (int i = 0; i < GC::MAX_GEESE; i++) {
		geese[i].init(rm, *p_d3d);
	}
	switch ((*GameStats::GetInstance()).getMode())
	{
	case start:
		startMode.init(rm, *p_d3d, track);
		break;
	case place:
		placeMode.init(rm, *p_d3d);
		break;
	case defend:
		defendMode.init(rm, *p_d3d, geese, bloons);
		break;
	case win:
		winMode.init(rm, *p_d3d, track);
		break;
	case lose:
		loseMode.init(rm, *p_d3d, track);
		break;
	default:
		break;
	}
	gpSpriteBatch = new SpriteBatch(&(*p_d3d).GetDeviceCtx());
	assert(gpSpriteBatch);
}
void Game::update(float dTime, Vector2 mousePos, bool isLMBPressed, bool keyboard[]) {
	Modes oldMode = (*GameStats::GetInstance()).getMode();
	switch (oldMode)
	{
	case start:
		startMode.update(dTime, mousePos, isLMBPressed);
		break;
	case place:
		placeMode.update(rm, dTime, mousePos, isLMBPressed, keyboard, geese, track);
		break;
	case defend:
		defendMode.update(rm, dTime, mousePos, isLMBPressed, keyboard, geese, bloons);
		break;
	case win:
		winMode.update(dTime, mousePos, isLMBPressed);
		break;
	case lose:
		loseMode.update(dTime, mousePos, isLMBPressed);
		break;
	default:
		break;
	}
	if ((*GameStats::GetInstance()).getMode() != oldMode) {
		changeState(oldMode);
	}
}
void Game::render(float dTime) {
	p_d3d->BeginRender({ 0, 0, 0, 0 });
	CommonStates dxstate(&(*p_d3d).GetDevice());
	gpSpriteBatch->Begin(SpriteSortMode_Deferred, dxstate.NonPremultiplied());

	switch ((*GameStats::GetInstance()).getMode())
	{
	case start:
		startMode.render(rm, *p_d3d, *gpSpriteBatch, dTime);
		break;
	case place:
		placeMode.render(rm, *p_d3d, *gpSpriteBatch, dTime, geese);
		//track.db_render(*p_d3d, rm, dTime, *gpSpriteBatch);
		break;
	case defend:
		defendMode.render(rm, *p_d3d, *gpSpriteBatch, dTime, geese, bloons);
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
void Game::changeState(Modes oldMode) {
	switch ((*GameStats::GetInstance()).getMode())
	{
	case start:
		startMode.init(rm, *p_d3d, track);
		break;
	case place:
		if (oldMode != defend) {
			defendMode.destroyGameObjects(bloons, geese);
			defendMode.reset(bloons);
		}
		placeMode.init(rm, *p_d3d);
		break;
	case defend:
		defendMode.init(rm, *p_d3d, geese, bloons);
		break;
	case win:
		winMode.init(rm, *p_d3d, track);
		break;
	case lose:
		loseMode.init(rm, *p_d3d, track);
		break;
	default:
		break;
	}
}