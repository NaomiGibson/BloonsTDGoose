#include "Resourcemanager.h"

void ResourceManager::release() {
	for (auto& pair : texCache)
		ReleaseCOM(pair.second);
	texCache.clear();
	for (auto& pair : fontCache)
		pair.second = nullptr;
	fontCache.clear();
	spritesheetCache.clear();
	for (auto& pair : object3DCache)
		pair.second.release();
	object3DCache.clear();
	vertexShader = nullptr;
	delete vertexShader;
	pixelShader = nullptr;
	delete pixelShader;
	gfxDataConstsBuffer = nullptr;
	delete gfxDataConstsBuffer;
	inputLayout = nullptr;
	delete inputLayout;
}
void ResourceManager::Object_3D::release() {
	idxBuffer = nullptr;
	delete idxBuffer;
	vertBuffer = nullptr;
	delete vertBuffer;
}


// FX

void ResourceManager::buildFX(MyD3D& d3d) {
	CheckShaderModel5Supported(d3d.GetDevice());

	// Create the constant buffers for the variables defined in the vertex shader.
	CreateConstantBuffer(d3d.GetDevice(), sizeof(GfxParamsPerObj), &gfxDataConstsBuffer);

	//load in a pre-compiled vertex shader
	char* pBuff = nullptr;
	unsigned int bytes = 0;
	pBuff = ReadAndAllocate("../bin/data/SimpleVS.cso", bytes);
	CreateVertexShader(d3d.GetDevice(), pBuff, bytes, vertexShader);
	//create a link between our data and the vertex shader
	CreateInputLayout(d3d.GetDevice(), VertexPosColour::sVertexDesc, 2, pBuff, bytes, &inputLayout);
	delete[] pBuff;

	//load in a pre-compiled pixel shader	
	pBuff = ReadAndAllocate("../bin/data/SimplePS.cso", bytes);
	CreatePixelShader(d3d.GetDevice(), pBuff, bytes, pixelShader);
	delete[] pBuff;

}
ID3D11VertexShader* ResourceManager::getVertexShader() {
	assert(vertexShader);
	return vertexShader;
}
ID3D11PixelShader* ResourceManager::getPixelShader() {
	assert(pixelShader);
	return pixelShader;
}
GfxParamsPerObj& ResourceManager::getGfxData() {
	return gfxData;
}
ID3D11Buffer* ResourceManager::getGfxDataConstsBuffer() {
	assert(gfxDataConstsBuffer);
	return gfxDataConstsBuffer;
}
ID3D11InputLayout* ResourceManager::getInputLayout() {
	assert(inputLayout);
	return inputLayout;
}


// 3D OBJECTS

string ResourceManager::buildObject3D(MyD3D& d3d, const string& objName, Vector3 size) {
	ResourceManager::Object_3D object3D;

	// Create vertex buffer for a pyramid
	VertexPosColour vertices[] =
	{
		{ Vector3(-size.x / 2, -size.y / 2, +size.z / 2), Colours::Magenta }, // bottom left
		{ Vector3(+size.x / 2, -size.y / 2, +size.z / 2), Colours::Yellow }, // bottom right
		{ Vector3(+size.x / 2, -size.y / 2, -size.z / 2), Colours::Cyan }, // bottom back
		{ Vector3(+size.x / 2, +size.y / 2, +size.z / 2), Colours::Green }, // top
	};
	CreateVertexBuffer(d3d.GetDevice(), sizeof(VertexPosColour) * 4, vertices, object3D.vertBuffer);

	UINT indices[] = {
		0, 1, 2,	// bottom
		3, 1, 0,	// front
		3, 0, 2,	// back left
		3, 2, 1,	// back right
	};
	CreateIndexBuffer(d3d.GetDevice(), sizeof(UINT) * 12, indices, object3D.idxBuffer);

	addObject3D(objName, object3D);
	return objName;
}
ResourceManager::Object_3D* ResourceManager::findObject3D(string objName) {
	Object3DMap::iterator it = object3DCache.find(objName);
	if (it != object3DCache.end())
		return &(*it).second;
	return nullptr;
}
ID3D11Buffer* ResourceManager::findVertBuffer(string objName) {
	return (*findObject3D(objName)).vertBuffer;
}
ID3D11Buffer* ResourceManager::findIdxBuffer(string objName) {
	return (*findObject3D(objName)).idxBuffer;
}

// SPRITESHEETS

string ResourceManager::loadSpritesheet(MyD3D& d3d, const wstring& fileName, const string& texName, int columns, int rows, int numSprites) {
	if (findSpritesheet(texName) == nullptr) 
	{
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
		addSprSheet(texName, sprSheet);
		return texName;
	}
	return texName;
}
ResourceManager::Spritesheet* ResourceManager::findSpritesheet(string sprSheetName) {
	SpritesheetMap::iterator it = spritesheetCache.find(sprSheetName);
	if (it != spritesheetCache.end())
		return &(*it).second;
	return nullptr;
}
RECT ResourceManager::findRect(string spritesheet, int spriteID) {
	Spritesheet& sprSheet = *findSpritesheet(spritesheet);
	assert(spriteID <= sprSheet.texRects.size());
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

void ResourceManager::addObject3D(string objName, Object_3D object3D) {
	object3DCache.insert(Object3DMap::value_type(objName, object3D));
}
void ResourceManager::addSprSheet(string texName, Spritesheet sprSheet) {
	spritesheetCache.insert(SpritesheetMap::value_type(texName, sprSheet));
}
void ResourceManager::addFont(string texName, DirectX::SpriteFont* font) {
	fontCache.insert(FontMap::value_type(texName, font));
}
