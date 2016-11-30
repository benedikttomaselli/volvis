#include "VolumeRender.h"


//performs raycasting at pixel (x,y)
//returns the maximum value
vector<int> VolumeRenderMIP::castRay(int x, int y, int zDim, bool invert, bool alt, int step, ViewDirection vd)
{
	float currValue = 0;
	float maxIntensity = 0;
	int retZ = 0;
	for (int z = 0; z <= zDim - step; z += step){
		currValue = getVoxelValue(x, y, z, vd);

		if (currValue > maxIntensity){
			maxIntensity = currValue;
			retZ = z;
		}
	}
	if (invert){
		maxIntensity = 1 - maxIntensity;

	}
	int c = round(maxIntensity * 255);
	//	return new QRgb(qRgb(c, c, c));
	return  vector<int> {c, c, c, retZ};

}

VolumeRenderMIP::VolumeRenderMIP(GradientShading* grad)
{
	gradient = grad;
}


VolumeRenderMIP::~VolumeRenderMIP()
{
}
