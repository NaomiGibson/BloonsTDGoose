#include "SpinningPyramid.h"

void SpinningPyramid::init(MyD3D& d3d, ResourceManager& rm) {
	meshName = "pyramid";
	rm.buildObject3D(d3d, meshName, { 1, 1, 1 });
}

void SpinningPyramid::render(MyD3D& d3d, ResourceManager& rm) {
	ResourceManager::Object_3D mesh;
	d3d.InitInputAssembler(inputLayout, mesh.vertBuffer, sizeof(VertexPosColour), mesh.idxBuffer);

	gfxData.wvp = world * view * proj;
	d3d.GetDeviceCtx().UpdateSubresource(pGfxDataConstsBuffer, 0, nullptr, &gfxData, 0, 0);

	d3d.GetDeviceCtx().VSSetConstantBuffers(0, 1, &pGfxDataConstsBuffer);
	d3d.GetDeviceCtx().DrawIndexed(4, 0, 0);
}