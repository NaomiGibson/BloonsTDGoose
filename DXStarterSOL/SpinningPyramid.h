#pragma once
#include "ResourceManager.h"

struct GfxParamsPerObj
{
	DirectX::SimpleMath::Matrix wvp;
};

class SpinningPyramid
{
private:
	string meshName = "default";
	Vector3 pos;
	Vector3 rotation;
	Vector3 vel;

	Matrix world;
	Matrix view;
	Matrix proj;
	GfxParamsPerObj gfxData;				//a structure containing data the gpu needs to render something
	ID3D11Buffer* pGfxDataConstsBuffer;		//a d3d object to copy the above data into, ends up in a constant register
	ID3D11InputLayout* inputLayout;			//vertex description
public:
	void init(MyD3D& d3d, ResourceManager& rm); // build cube
	void update(MyD3D& d3d, ResourceManager& rm); // calculate verts based on rotation
	void render(MyD3D& d3d, ResourceManager& rm); // draw pyramid
};

