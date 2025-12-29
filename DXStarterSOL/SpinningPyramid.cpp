#include "SpinningPyramid.h"

void SpinningPyramid::init(MyD3D& d3d, ResourceManager& rm) {
	meshName = "pyramid";
	rm.buildObject3D(d3d, meshName, { 1, 1, 1 });
}

void SpinningPyramid::render(MyD3D& d3d, ResourceManager& rm) {

}