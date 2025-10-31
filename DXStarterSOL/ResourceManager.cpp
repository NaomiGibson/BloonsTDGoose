#include "Resourcemanager.h"

void ResourceManager::release() {
	for (auto& pair : texCache)
		ReleaseCOM(pair.second);
	texCache.clear();
	for (auto& pair : fontCache)
		pair.second = nullptr;
	fontCache.clear();
	spritesheetCache.clear();
}

// SPRITESHEETS

ResourceManager::Spritesheet ResourceManager::loadSpritesheet(MyD3D& d3d, const wstring& fileName, const string& texName, int columns, int rows, int numSprites) {
	ID3D11ShaderResourceView* tex = findTex(loadTexture(d3d, fileName, texName));
	Spritesheet sprSheet;
	sprSheet.texName = texName;

	ID3D11Resource* pResource = nullptr;
	ID3D11Texture2D* pTexture2D = nullptr;
	unsigned int width;
	unsigned int height;

	tex->GetResource(&pResource);
	pResource->QueryInterface<ID3D11Texture2D>(&pTexture2D);
	D3D11_TEXTURE2D_DESC desc;
	pTexture2D->GetDesc(&desc);
	width = desc.Width;
	height = desc.Height;

	int sprW = width / columns;
	int sprH = height / rows;

	int r(0), c(0);
	for (int i = 0; i < numSprites; i++)
	{
		sprSheet.texRects.push_back({ sprW * c,  sprH * r, sprW * (c + 1), sprH * (r + 1) });
		c++;
		if (c >= columns) {
			r++;
			c = 0;
		}
	}

	//for (int r = 1; r < rows; r++) {
	//	for (int c = 1; c < columns; c++) {
	//	}
	//}
	addSprSheet(texName, sprSheet);
	return sprSheet;
}
ResourceManager::Spritesheet ResourceManager::findSpritesheet(string sprSheetName) {
	SpritesheetMap::iterator it = spritesheetCache.find(sprSheetName);
	if (it != spritesheetCache.end())
		return (*it).second;
}
RECT ResourceManager::findRect(string spritesheet, int spriteID) {
	Spritesheet sprSheet = findSpritesheet(spritesheet);
	assert(spriteID < sprSheet.texRects.size());
	return sprSheet.texRects[spriteID - 1];
}

// TEXTURES

//look it up using the key
ID3D11ShaderResourceView* ResourceManager::findTex(string texName) {
	assert(texName != "");
	TexMap::iterator it = texCache.find(texName);
	if (it != texCache.end())
		return (*it).second;
	return nullptr;
}
//look it up slowly if you don’t have the key – try to avoid
ID3D11ShaderResourceView* ResourceManager::findTex(ID3D11ShaderResourceView* pTex) {
	TexMap::iterator it = texCache.begin();
	ID3D11ShaderResourceView *p = nullptr;
	while (it != texCache.end() && !p)
	{
		if ((*it).second == pTex)
			p = (*it).second;
		++it;
	}
	assert(p);
	return p;
}
void ResourceManager::addTex(string texName, ID3D11ShaderResourceView* tex) {
	texCache.insert(TexMap::value_type(texName, tex));
}
string ResourceManager::loadTexture(MyD3D& d3d, const wstring& fileName, const string& texName) {
	if (!findTex(texName)) {// if it is not already loaded
		DDS_ALPHA_MODE alpha; // load the texture
		ID3D11ShaderResourceView* tex;
		if (CreateDDSTextureFromFile(&d3d.GetDevice(), fileName.c_str(), nullptr, &tex, 0, &alpha) != S_OK) {
			WDBOUT(L"Cannot load " << fileName.c_str() << L"\n");
			assert(false);
		}
		assert(tex);
		texCache.insert(pair<string, ID3D11ShaderResourceView*>(texName, tex)); // add to cache
		return texName;
	}
	else
		return texName; // if already loaded, return the version already in cache
}


// FONTS

//look it up using the key
DirectX::SpriteFont* ResourceManager::findFont(string fontName) {
	FontMap::iterator it = fontCache.find(fontName);
	if (it != fontCache.end())
		return (*it).second;
	return nullptr;
}
//look it up slowly if you don’t have the key – try to avoid
DirectX::SpriteFont* ResourceManager::findFont(DirectX::SpriteFont* pFont) {
	FontMap::iterator it = fontCache.begin();
	DirectX::SpriteFont* p = nullptr;
	while (it != fontCache.end() && !p)
	{
		if ((*it).second == pFont)
			p = (*it).second;
		++it;
	}
	assert(p);
	return p;
}
DirectX::SpriteFont* ResourceManager::loadFont(MyD3D& d3d, const wstring& fileName, const string& fontName) {
	if (!findTex(fontName)) {// if it is not already loaded
		DDS_ALPHA_MODE alpha; // load the texture
		DirectX::SpriteFont* font = new SpriteFont(&d3d.GetDevice(), fileName.c_str());
		if (!font) {
			WDBOUT(L"Cannot load " << fileName.c_str() << L"\n");
			assert(false);
		}
		fontCache.insert(pair<string, DirectX::SpriteFont*>(fontName, font)); // add to cache
		return font;
	}
	else
		return findFont(fontName); // if already loaded, return the version already in cache
}

// ADD TO MAPS

void ResourceManager::addSprSheet(string texName, Spritesheet sprSheet) {
	spritesheetCache.insert(SpritesheetMap::value_type(texName, sprSheet));
}
void ResourceManager::addFont(string texName, DirectX::SpriteFont* font) {
	fontCache.insert(FontMap::value_type(texName, font));
}
