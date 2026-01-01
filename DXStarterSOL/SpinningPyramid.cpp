#include "SpinningPyramid.h"

void SpinningPyramid::init(MyD3D& d3d, ResourceManager& rm) {
	meshName = "pyramid";
	rm.buildObject3D(d3d, meshName, { 1, 1, 1 });
}

void SpinningPyramid::render(MyD3D& d3d, ResourceManager& rm) {
	ResourceManager::Object_3D* mesh = rm.findObject3D(meshName);
	d3d.InitInputAssembler(rm.getInputLayout(), (*mesh).vertBuffer, sizeof(VertexPosColour), (*mesh).idxBuffer);

	rm.getGfxData().wvp = world * view * proj;
	d3d.GetDeviceCtx().UpdateSubresource(rm.getGfxDataConstsBuffer(), 0, nullptr, &rm.getGfxData(), 0, 0);

	ID3D11Buffer* gfxDataConstsBuffer = rm.getGfxDataConstsBuffer();
	
	d3d.GetDeviceCtx().VSSetConstantBuffers(0, 1, &gfxDataConstsBuffer);
	d3d.GetDeviceCtx().DrawIndexed(4, 0, 0);
}