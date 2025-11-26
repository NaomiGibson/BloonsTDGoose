#include "PlaceMode.h"

void PlaceMode::init(ResourceManager& rm, MyD3D& d3d) {
	rm.loadFont(d3d, L"../bin/data/Moghul.spritefont", "Moghul");
	spr_bg.init(rm.loadTexture(d3d, L"../bin/data/BloonsMap.dds", "mainBackground"), { 0, 0, 1920, 1080 }, { 0, 0 }, 0, { 1, 1 });
	ui_stats.init(d3d, rm, (*GameStats::GetInstance()).getLives(), (*GameStats::GetInstance()).getCoins(), (*GameStats::GetInstance()).getRound(), GC::MAX_ROUNDS);
	string texName = rm.loadTexture(d3d, L"../bin/data/PlayIcon64.dds", "playIcon64");
	btn_play.init(d3d, rm, { 64, 64 }, texName, { 0, 0, 64, 64 }, { 1840, 996 }, 0, { 1, 1 });
	texName = rm.loadTexture(d3d, L"../bin/data/ExitIcon.dds", "ExitIcon");
	btn_exit.init(d3d, rm, { 128, 128 }, texName, { 0, 0, 128, 128 }, { 84, 980 }, 0, { 1, 1 });
	ResourceManager::Spritesheet sprsheet = rm.loadSpritesheet(d3d, L"../bin/data/Geese.dds", "goose", 4, 4, 12);
	btn_placeGoose.init(d3d, rm, sprsheet.texName, 1, { 1680, 600 }, 90, 20);
	ui_goosePlacer.init(rm, d3d);
	ui_gooseUpgrades.init(d3d, rm);
}
void PlaceMode::update(ResourceManager& rm, float dTime, Vector2 mousePos, bool isLMBPressed, bool keyboard[], Goose geese[], Track& track) {
	// update geese and tower selection
	static bool lastIsLMBPressed = false;
	bool newGooseSelected = false;
	for (int i(0); i < GC::MAX_GEESE; i++) {
		geese[i].updatePlace(dTime, mousePos, isLMBPressed);
		if (geese[i].getTriggerClick()) { // select goose when it is clicked
			if (selectedGoose != -1)
				deselectGoose(rm, geese);
			selectGoose(rm, geese, i);
			newGooseSelected = true;
		}
	}

	//update game objects
	btn_play.update(dTime, mousePos, isLMBPressed);
	btn_exit.update(dTime, mousePos, isLMBPressed);
	btn_placeGoose.update(rm, dTime, mousePos, isLMBPressed);
	if (btn_placeGoose.getTriggerClick())
		ui_goosePlacer.activate();
	ui_goosePlacer.update(rm, mousePos, isLMBPressed, geese, track, ui_stats);
	ui_gooseUpgrades.update(rm, dTime, mousePos, isLMBPressed);
	ui_stats.update(rm, dTime);

	purchaseUpgrade(rm, geese);

	// tower deselection
	if(!newGooseSelected && isLMBPressed && !lastIsLMBPressed && !btn_placeGoose.getTriggerClick() && ui_gooseUpgrades.getUpgradePurchased() == none) { // deselect goose on first frame of a click, not on a goose or button
		deselectGoose(rm, geese);
		lastIsLMBPressed = true;
	}
	lastIsLMBPressed = isLMBPressed;

	//After updating everything, decide current state
	if (btn_exit.getButton().getIsBtnDown())
		(*GameStats::GetInstance()).setMode(Modes::start);
	if (btn_play.getButton().getIsBtnDown()) {
		deselectGoose(rm, geese);
		(*GameStats::GetInstance()).setMode(Modes::defend);

	}
}
void PlaceMode::render(ResourceManager& rm, MyD3D& d3d, DirectX::SpriteBatch& sprBatch, float dTime, Goose geese[]) {
	spr_bg.render(d3d, rm, dTime, sprBatch);
	for (int i(0); i < GC::MAX_GEESE; i++) {
		geese[i].render(d3d, rm, dTime, sprBatch);
	}
	ui_stats.render(d3d, rm, dTime, sprBatch);
	btn_play.render(d3d, rm, dTime, sprBatch);
	btn_exit.render(d3d, rm, dTime, sprBatch);
	btn_placeGoose.render(d3d, rm, dTime, sprBatch);
	ui_goosePlacer.render(d3d, rm, dTime, sprBatch);
	ui_gooseUpgrades.render(d3d, rm, dTime, sprBatch);
}

void PlaceMode::selectGoose(ResourceManager& rm, Goose geese[], int idx) {
	upgrades u1 = none;
	upgrades u2 = none;
	upgrades u3 = none;
	geese[idx].selectPurchasableUpgrades(u1, u2, u3);
	ui_gooseUpgrades.activate(rm, u1, u2, u3);
	selectedGoose = idx;
	geese[idx].select();
}
void PlaceMode::deselectGoose(ResourceManager& rm, Goose geese[]) {
	ui_gooseUpgrades.deactivate();
	geese[selectedGoose].deselect();
	selectedGoose = -1;
}
void PlaceMode::purchaseUpgrade(ResourceManager& rm, Goose geese[]) {
	if (selectedGoose != -1) {									// if a goose is selected
		upgrades upgradePurchased = ui_gooseUpgrades.getUpgradePurchased();
		if (upgradePurchased != none) {							// and there is an upgrade to purchase
			if ((*GameStats::GetInstance()).getCoins() >= GC::UPGRADE_PRICES.at(upgradePurchased)) { // and the player can afford to buy it
				if (geese[selectedGoose].applyUpgrade(rm, upgradePurchased)) {		// and the new upgrade is compatible with those already applied
					(*GameStats::GetInstance()).spendCoins(GC::UPGRADE_PRICES.at(upgradePurchased)); // apply the upgrade
					ui_stats.setCoins((*GameStats::GetInstance()).getCoins());						
					upgrades u1, u2, u3;
					geese[selectedGoose].selectPurchasableUpgrades(u1, u2, u3);
					ui_gooseUpgrades.activate(rm, u1, u2, u3);
				}
			}
		}
	}
}