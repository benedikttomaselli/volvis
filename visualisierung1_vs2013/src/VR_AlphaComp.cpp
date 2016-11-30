//Kolb Mathias, 0625588
//Tomaselli Benedikt, 0926048

#include "VR.h"




VR_AlphaCompositing::VR_AlphaCompositing(Shading* shading)
{
	shading = shading;
}


vector<int> VR_AlphaCompositing::castRay(int x, int y, int zDim, bool invert, bool alt, int step, ViewDirection vd)
{

	vector<int> color = { 0, 0, 0 };
	vector<int> currValue = { 0, 0, 0 };
	float alpha = 0;
	float sumAlpha = 0;
	for (int z = 0; z < zDim - step; z = z + step){

		if (sumAlpha < 1){
			float temp = getVoxelValue(x, y, z, vd);
			alpha = temp;
			currValue = transfer(temp, invert);
			color = Over(currValue, color, alpha);
		}
		sumAlpha += alpha;
	}


	//	return new QRgb(qRgb(color[0], color[1], color[2]));
	return vector<int> {color[0], color[1], color[2], 0};


}

vector<int> VR_AlphaCompositing::transfer(float value, bool invert){
	vector<int> ret(3);
	ret[0] = round(abs((1 - invert) - value) * 255);
	ret[1] = round(abs(invert - value) * 255);
	//	ret[1] = 0;
	ret[2] = 0;
	return ret;

}

vector<int> VR_AlphaCompositing::Over(vector<int> a, vector<int> b, float alpha){
	vector<int> ret(3);
	for (int i = 0; i < 3; i++){
		ret[i] = round(alpha*a[i] + (1 - alpha)*b[i]);
	}
	return ret;
}

VR_AlphaCompositing::~VR_AlphaCompositing()
{

}
