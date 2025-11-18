#pragma once
#include <windows.h>
#include <string>
#include <unordered_map>
#include <cassert>
#include <d3d11.h>
#include <iomanip>
#include <vector>

#include "WindowUtils.h"
#include "D3DUtil.h"
#include "D3D.h"
#include "SimpleMath.h"
#include "SpriteFont.h"
#include "DDSTextureLoader.h"
#include "CommonStates.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

class ResourceManager
{
public:
	// values of a 
	struct Spritesheet {
		string texName;
		vector<RECT> texRects;
	};
	typedef unordered_map<string, ID3D11ShaderResourceView*> TexMap;
	typedef unordered_map<string, Spritesheet> SpritesheetMap;
	typedef unordered_map<string, DirectX::SpriteFont*> FontMap;

	void release();

	// TEXTURES

	// For loading a single texture into cache
	// if texture already exists, nothing is loaded and the pre-existing version is returned
	// Use loadSpritesheet for a texture atlas
	string loadTexture(MyD3D& d3d, const wstring& fileName, const string& texName); 
	// return a texture given its name
	ID3D11ShaderResourceView* findTex(string texName);
	// return a texture given a copy of the texture
	// - slow, prefer finding by key (texName)
	ID3D11ShaderResourceView* findTex(ID3D11ShaderResourceView* pTex);

	// SPRITESHEETS

	// Load a spritesheet into cache, saving the texture rect of each sprite
	// After loading, sprites are accessable by index (1 - numSprites)
	// if spritesheet already exists, nothing is loaded and the pre-existing version is returned
	Spritesheet loadSpritesheet(MyD3D& d3d, const wstring& fileName, const string& texName, int rows_, int columns_, int numSprites);
	// return spritesheet already loaded in cache given its name
	Spritesheet findSpritesheet(string sprSheetName);
	// return the rect of the given sprite on a spritesheet
	RECT findRect(string spritesheet, int spriteID); 

	// FONTS

	// load font into cache
	// if font already exists, nothing is loaded and the pre-existing version is returned
	DirectX::SpriteFont* loadFont(MyD3D& d3d, const wstring& fileName, const string& texName);
	// find font already loaded in cache given its name
	DirectX::SpriteFont* findFont(string fontName);
	// find font already loaded in cache given a copy of the font
	// - slow, prefer finding by key (fontName)
	DirectX::SpriteFont* findFont(DirectX::SpriteFont* pFont);
private:
	void addFont(string texName, DirectX::SpriteFont* font);
	void addTex(string texName, ID3D11ShaderResourceView* tex);
	void addSprSheet(string texName, Spritesheet sprSheet);
	TexMap texCache;
	SpritesheetMap spritesheetCache;
	FontMap fontCache;
};