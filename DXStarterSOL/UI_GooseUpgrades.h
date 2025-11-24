#pragma once
#include "Sprite.h"
#include "Text.h"
#include "Button.h"
#include "Utils.h"

class UI_PurchaseBtn
{
private:
	Button btn;
	Text txt_cost;
	Sprite spr_base;
	Sprite spr_purchaseIcon;
	string unfocusedTexName{ "buttonBase" };
	string focusedTexName{ "filledButtonBase" };
	string disabledTexName{ "disabledButtonBase" };
	int cost{ 0 };
	bool isEnabled = true;
public:
	// purchase icon sprite must be loaded before purchase button initialisation
	void init(MyD3D& d3d, ResourceManager& rm, string purcahseIconTexName, RECT texRect, Vector2 pos_, float rotation_, int cost_);
	void init(MyD3D& d3d, ResourceManager& rm, string purchaseIconSprsheetName, int purchaseIconIdx, Vector2 pos_, float rotation_, int cost_);
	void update(ResourceManager& rm, float dTime, Vector2 mousePos, bool isLMBPressed);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	void activate(ResourceManager& rm, string purchaseIconTexName, int cost_, bool isEnabled_);
	void activate(ResourceManager& rm, string purchaseIconTexName, int texIdx, int cost_, bool isEnabled_);
	bool getTriggerClick() { return (isEnabled && btn.getTriggerClick()); }
};

class UI_GooseUpgrades
{
	UI_PurchaseBtn btn_upgrade1;
	UI_PurchaseBtn btn_upgrade2;
	UI_PurchaseBtn btn_upgrade3;
	Text txt_focusedName; // the name of the focused upgrade
	upgrades upgrade1 = none;
	upgrades upgrade2 = none;
	upgrades upgrade3 = none;
	bool isActive{ false };
public:
	void init(MyD3D& d3d, ResourceManager& rm);
	void update(ResourceManager& rm, float dTime, Vector2 mousePos, bool isLMBPressed);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	void activate(ResourceManager& rm, upgrades upgrade_1, upgrades upgrade_2, upgrades upgrade_3);
	void deactivate() { isActive = false; }
	// @return upgrade of button currently clicked, if any
	upgrades getUpgradePurchased();
};

