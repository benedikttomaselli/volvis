#include "VolumeRender.h"


vector<int> VolumeRenderFirstHit::castRay(int x, int y, int zDim, bool invert, bool alt, int step, ViewDirection vd){
	float currValue = 0;
	bool found = false;
	int retZ=0;
	for (int z = 0; z <= zDim - step && !found; z += step){
		currValue = getVoxelValue(x, y, z, vd);
		if (currValue > threshold){
			retZ = z;
			found = true;
		}
	}
	int c = round(currValue * 255);
	//return new QRgb(qRgb(c, c, 0));
	return vector<int> {c, c, 0, retZ};
}

void VolumeRenderFirstHit::setThreshold(float t){
	if (0 <= t && t <= 1){
		threshold = t;
	}
}


VolumeRenderFirstHit::VolumeRenderFirstHit(GradientShading* grad)
{
	gradient = grad;
}


VolumeRenderFirstHit::~VolumeRenderFirstHit()
{
}
