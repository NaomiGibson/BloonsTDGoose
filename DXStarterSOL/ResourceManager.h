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
	ID3D11ShaderResourceView* findTex(string texName);
	ID3D11ShaderResourceView* findTex(ID3D11ShaderResourceView* pTex);
	string loadTexture(MyD3D& d3d, const wstring& fileName, const string& texName); // For loading a single texture. Use Spritesheet::loadSpritesheet for a texture atlas

	string loadSpritesheet(MyD3D& d3d, const wstring& fileName, const string& texName, int rows_, int columns_, int numSprites);
	Spritesheet findSpritesheet(string sprSheetName);
	RECT findRect(string texName, int spriteID);
	//RECT findRect(ID3D11ShaderResourceView* pTex, int spriteID);

	DirectX::SpriteFont* findFont(string fontName);
	DirectX::SpriteFont* findFont(DirectX::SpriteFont* pFont);
	DirectX::SpriteFont* loadFont(MyD3D& d3d, const wstring& fileName, const string& texName);
private:
	void addFont(string texName, DirectX::SpriteFont* font);
	void addTex(string texName, ID3D11ShaderResourceView* tex);
	void addSprSheet(string texName, Spritesheet sprSheet);
	TexMap texCache;
	SpritesheetMap spritesheetCache;
	FontMap fontCache;
}; 