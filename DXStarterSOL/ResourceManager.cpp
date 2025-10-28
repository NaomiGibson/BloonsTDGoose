#include "Resourcemanager.h"

void ResourceManager::release() {
	for (auto& pair : texCache)
		ReleaseCOM(pair.second);
	texCache.clear();
	for (auto& pair : fontCache)
		pair.second = nullptr;
	fontCache.clear();
}
//look it up using the key
ID3D11ShaderResourceView* ResourceManager::findTex(string texName) {
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
ID3D11ShaderResourceView* ResourceManager::loadTexture(MyD3D& d3d, const wstring& fileName, const string& texName) {
	if (!findTex(texName)) {// if it is not already loaded
		DDS_ALPHA_MODE alpha; // load the texture
		ID3D11ShaderResourceView* tex;
		if (CreateDDSTextureFromFile(&d3d.GetDevice(), fileName.c_str(), nullptr, &tex, 0, &alpha) != S_OK) {
			WDBOUT(L"Cannot load " << fileName.c_str() << L"\n");
			assert(false);
		}
		assert(tex);
		texCache.insert(pair<string, ID3D11ShaderResourceView*>(texName, tex)); // add to cache
		return tex;
	}
	else
		return findTex(texName); // if already loaded, return the version already in cache
}

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

void ResourceManager::addFont(string texName, DirectX::SpriteFont* font) {
	fontCache.insert(FontMap::value_type(texName, font));
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


