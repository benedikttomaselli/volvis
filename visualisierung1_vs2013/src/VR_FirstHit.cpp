//Kolb Mathias, 0625588
//Tomaselli Benedikt, 0926048

#include "VR.h"


vector<int> VR_FirstHit::castRay(int x, int y, int zDim, bool invert, bool alt, int step, ViewDirection vd){
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

void VR_FirstHit::setThreshold(float t){
	if (0 <= t && t <= 1){
		threshold = t;
	}
}


VR_FirstHit::VR_FirstHit(Shading* shading)
{
	shading = shading;
}


VR_FirstHit::~VR_FirstHit()
{
}
