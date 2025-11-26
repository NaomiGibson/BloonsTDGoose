#include "UI_GooseUpgrades.h"

// PURCHASE BUTTON

void UI_PurchaseBtn::init(MyD3D& d3d, ResourceManager& rm, string purchaseIconTexName, RECT purchaseIconTexRect, Vector2 pos_, float rotation_, int cost_) {
	int cost = cost_;
	spr_base.init(rm.loadTexture(d3d, L"../bin/data/buttonBase.dds", "buttonBase"), { 0, 0, 96, 96 }, pos_, rotation_, { 1.f, 1.f });
	rm.loadTexture(d3d, L"../bin/data/filledButtonBase.dds", "filledButtonBase");
	rm.loadTexture(d3d, L"../bin/data/disabledButtonBase.dds", "disabledButtonBase");
	spr_base.setOrigin({ 0.5f, 0.5f });
	spr_purchaseIcon.init(purchaseIconTexName, purchaseIconTexRect, pos_, rotation_, { 1, 1 });
	spr_purchaseIcon.setOrigin({ 0.5f, 0.5f });
	btn.init(rm, d3d, pos_, spr_base.GetScreenSize().x / 2);
	txt_cost = Text{ "Moghul", "$ " + to_string(cost), { pos_.x - spr_base.GetScreenSize().y / 2, pos_.y + spr_base.GetScreenSize().y / 2 + 10 }, { 0, 0, 0, 1 } };
}
void UI_PurchaseBtn::init(MyD3D& d3d, ResourceManager& rm, string purchaseIconSprsheetName, int purchaseIconIdx, Vector2 pos_, float rotation_, int cost_) {
	int cost = cost_;
	spr_base.init(rm.loadTexture(d3d, L"../bin/data/buttonBase.dds", "buttonBase"), { 0, 0, 96, 96 }, pos_, rotation_, { 1.f, 1.f });
	rm.loadTexture(d3d, L"../bin/data/filledButtonBase.dds", "filledButtonBase");
	rm.loadTexture(d3d, L"../bin/data/disabledButtonBase.dds", "disabledButtonBase");
	spr_base.setOrigin({ 0.5f, 0.5f });
	spr_purchaseIcon.init(purchaseIconSprsheetName, rm.findRect(purchaseIconSprsheetName, purchaseIconIdx), pos_, rotation_, {1, 1});
	spr_purchaseIcon.setOrigin({ 0.5f, 0.5f });
	btn.init(rm, d3d, pos_, spr_base.GetScreenSize().x / 2);
	txt_cost = Text{ "Moghul", "$" + to_string(cost), { pos_.x - spr_base.GetScreenSize().y / 2 + 5, pos_.y + spr_base.GetScreenSize().y / 2 + 5 }, { 0, 0, 0, 1 } };
}
void UI_PurchaseBtn::update(ResourceManager& rm, float dTime, Vector2 mousePos, bool isLMBPressed) {
	btn.update(dTime, mousePos, isLMBPressed);
	if (isEnabled && btn.getTriggerBeginHover())
		spr_base.setTexName(focusedTexName);
	else if (isEnabled && !btn.getIsHovered())
		spr_base.setTexName(unfocusedTexName);
}
void UI_PurchaseBtn::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	txt_cost.render(d3d, rm, dTime, batch);
	spr_base.render(d3d, rm, dTime, batch);
	spr_purchaseIcon.render(d3d, rm, dTime, batch);
}
void UI_PurchaseBtn::activate(ResourceManager& rm, string purchaseIconTexName, int texIdx, int cost_, bool isEnabled_) {
	cost = cost_;
	txt_cost.setMsg("$" + to_string(cost));
	isEnabled = isEnabled_;
	if (isEnabled) {
		spr_purchaseIcon.setTexName(purchaseIconTexName);
		spr_purchaseIcon.setTexRect(rm.findRect(purchaseIconTexName, texIdx));
		spr_purchaseIcon.setIsActive(true);
		spr_base.setTexName(unfocusedTexName);
	}
	else {
		spr_purchaseIcon.setIsActive(false);		
		spr_base.setTexName(disabledTexName);
	}
}
void UI_PurchaseBtn::activate(ResourceManager& rm, string purchaseIconTexName, int cost_, bool isEnabled_) {
	cost = cost_;
	txt_cost.setMsg("$" + to_string(cost));
	isEnabled = isEnabled_;
	if (isEnabled) {
		spr_purchaseIcon.setTexName(purchaseIconTexName);		
		spr_base.setTexName(unfocusedTexName);
	}
	else {
		spr_purchaseIcon.setIsActive(false);
		spr_base.setTexName(disabledTexName);
	}

}

// GOOSE UPGRADES INTERFACE

void UI_GooseUpgrades::init(MyD3D& d3d, ResourceManager& rm) {
	btn_upgrade1.init(d3d, rm, rm.loadSpritesheet(d3d, L"../bin/data/upgradeIcons.dds", "upgradeIcons", 2, 3, 6).texName, 1, pos + Vector2{ 48, 85 }, 0, 10);
	btn_upgrade2.init(d3d, rm, rm.findSpritesheet("upgradeIcons").texName, 1, pos + Vector2{ 148, 85 }, 0, 10);
	btn_upgrade3.init(d3d, rm, rm.findSpritesheet("upgradeIcons").texName, 1, pos + Vector2{ 248, 85 }, 0, 10);
	txt_focusedName = Text{ "Moghul", "Upgrade Name", pos, { 0, 0, 0, 1 } };
}
void UI_GooseUpgrades::update(ResourceManager& rm, float dTime, Vector2 mousePos, bool isLMBPressed) {
	if (isActive) {
		btn_upgrade1.update(rm, dTime, mousePos, isLMBPressed);
		btn_upgrade2.update(rm, dTime, mousePos, isLMBPressed);
		btn_upgrade3.update(rm, dTime, mousePos, isLMBPressed);
		if (btn_upgrade1.getIsHovered())
			focusUpgrade(upgrade1);
		else if (btn_upgrade2.getIsHovered())
			focusUpgrade(upgrade2);
		else if (btn_upgrade3.getIsHovered())
			focusUpgrade(upgrade3);
	}
}
void UI_GooseUpgrades::render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch) {
	if (isActive) {
		btn_upgrade1.render(d3d, rm, dTime, batch);
		btn_upgrade2.render(d3d, rm, dTime, batch);
		btn_upgrade3.render(d3d, rm, dTime, batch);
		txt_focusedName.render(d3d, rm, dTime, batch);
	}
}
void UI_GooseUpgrades::activate(ResourceManager& rm, upgrades upgrade_1, upgrades upgrade_2, upgrades upgrade_3) {
	btn_upgrade1.activate(rm, "upgradeIcons", (int)upgrade_1 + 1, GC::UPGRADE_PRICES.at(upgrade_1), upgrade_1 != none);
	btn_upgrade2.activate(rm, "upgradeIcons", (int)upgrade_2 + 1, GC::UPGRADE_PRICES.at(upgrade_2), upgrade_2 != none);
	btn_upgrade3.activate(rm, "upgradeIcons", (int)upgrade_3 + 1, GC::UPGRADE_PRICES.at(upgrade_3), upgrade_3 != none);
	upgrade1 = upgrade_1;
	upgrade2 = upgrade_2;
	upgrade3 = upgrade_3;
	isActive = true;
}
upgrades UI_GooseUpgrades::getUpgradePurchased() {
	if (btn_upgrade1.getTriggerClick())
		return upgrade1;
	if (btn_upgrade2.getTriggerClick())
		return upgrade2;
	if (btn_upgrade3.getTriggerClick())
		return upgrade3;
	return upgrades::none;
}
void UI_GooseUpgrades::focusUpgrade(upgrades focusedUpgrade) {
	txt_focusedName.setMsg(GC::UPGRADE_NAMES.at(focusedUpgrade));
}
void UI_GooseUpgrades::unfocusUpgrade() {
	txt_focusedName.setMsg("Purchase Upgrade");
}