#include "Game.h"

Game::Game(MyD3D* d3d_) 
:	p_d3d(d3d_) {
}
void Game::release() {
	rm.release();
}

void Game::init() {
	rm.buildFX(*p_d3d);
	//widely used game objects
	string texName = rm.loadTexture(*p_d3d, L"../bin/data/ExitIcon.dds", "ExitIcon");
	btn_exit.init(*p_d3d, rm, { 128, 128 }, texName, { 0, 0, 128, 128 }, { 84, 980 }, 0, { 1, 1 });
	track.init(rm, *p_d3d);
	bloons.init(rm, *p_d3d);
	for (int i = 0; i < GC::MAX_GEESE; i++) {
		geese[i].init(rm, *p_d3d);
	}
	// gamemodes
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
		btn_exit.update(dTime, mousePos, isLMBPressed);
		if (btn_exit.getButton().getTriggerClick())
			(*GameStats::GetInstance()).setMode(quit);
		break;
	case place:
		btn_exit.update(dTime, mousePos, isLMBPressed);
		if (btn_exit.getButton().getTriggerClick())
			(*GameStats::GetInstance()).setMode(start);
		placeMode.update(rm, dTime, mousePos, isLMBPressed, keyboard, geese, track);
		break;
	case defend:
		defendMode.update(rm, dTime, mousePos, isLMBPressed, keyboard, geese, bloons);
		break;
	case win:
		btn_exit.update(dTime, mousePos, isLMBPressed);
		if (btn_exit.getButton().getTriggerClick())
			(*GameStats::GetInstance()).setMode(start);
		winMode.update(dTime, mousePos, isLMBPressed);
		break;
	case lose:
		btn_exit.update(dTime, mousePos, isLMBPressed);
		if (btn_exit.getButton().getTriggerClick())
			(*GameStats::GetInstance()).setMode(start);
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
	p_d3d->GetDeviceCtx().VSSetShader(rm.getVertexShader(), nullptr, 0);
	p_d3d->GetDeviceCtx().PSSetShader(rm.getPixelShader(), nullptr, 0);
	CommonStates dxstate(&(*p_d3d).GetDevice());
	gpSpriteBatch->Begin(SpriteSortMode_Deferred, dxstate.NonPremultiplied());

	switch ((*GameStats::GetInstance()).getMode())
	{
	case start:
		startMode.render(rm, *p_d3d, *gpSpriteBatch, dTime);
		btn_exit.render(*p_d3d, rm, dTime, *gpSpriteBatch);
		break;
	case place:
		placeMode.render(rm, *p_d3d, *gpSpriteBatch, dTime, geese);
		btn_exit.render(*p_d3d, rm, dTime, *gpSpriteBatch);
		break;
	case defend:
		defendMode.render(rm, *p_d3d, *gpSpriteBatch, dTime, geese, bloons);
		break;
	case win:
		winMode.render(rm, *p_d3d, *gpSpriteBatch, dTime);
		btn_exit.render(*p_d3d, rm, dTime, *gpSpriteBatch);
		break;
	case lose:
		loseMode.render(rm, *p_d3d, *gpSpriteBatch, dTime);
		btn_exit.render(*p_d3d, rm, dTime, *gpSpriteBatch);
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