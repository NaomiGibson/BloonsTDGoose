#pragma once
#include "Sprite.h"
#include "Text.h"
#include "Button.h"

class UI_PurchaseBtn
{
private:
	Button btn;
	Text txt_cost;
	Sprite spr_base;
	Sprite spr_purchaseIcon;
	string unfocusedTexName{ "buttonBase" };
	string focusedTexName{ "filledButtonBase" };
	int cost{ 0 };
public:
	// purchase icon sprite must be loaded before purchase button initialisation
	void init(MyD3D& d3d, ResourceManager& rm, string purcahseIconTexName, RECT texRect, Vector2 pos_, float rotation_, int cost);
	void init(MyD3D& d3d, ResourceManager& rm, string purchaseIconSprsheetName, int purchaseIconIdx, Vector2 pos_, float rotation_, int cost_);
	void update(ResourceManager& rm, float dTime, Vector2 mousePos, bool isLMBPressed);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	bool getTriggerClick() { return btn.getTriggerClick(); }
};

class UI_GooseUpgrades
{
	UI_PurchaseBtn btn_upgrade1;
	UI_PurchaseBtn btn_upgrade2;
	UI_PurchaseBtn btn_upgrade3;
	bool isActive{ false };
public:
	void init(MyD3D& d3d, ResourceManager& rm);
	void update(ResourceManager& rm, float dTime, Vector2 mousePos, bool isLMBPressed);
	void render(MyD3D& d3d, ResourceManager& rm, float dTime, SpriteBatch& batch);
	void activate() { isActive = true; }
	void deactivate() { isActive = false; }
};

