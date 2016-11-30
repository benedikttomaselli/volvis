#include "GradientShading.h"

using namespace std;

GradientShading::GradientShading()
{

	xKernel = { -1, 0, 1,
		-2, 0, 2,
		-1, 0, 1,

		-2, 0, 2,
		-4, 0, 4,
		-2, 0, 2,

		-1, 0, 1,
		-2, 0, -2,
		-1, 0, -1 };


	yKernel = { 1, 2, 1,
		0, 0, 0,
		-1, -2, -1,

		2, 4, 2,
		0, 0, 0,
		-2, -4, -2,

		1, 2, 1,
		0, 0, 0,
		-1, -2, -1 };


	zKernel = { 1, 2, 1,
		2, 4, 2,
		1, 2, 1,

		0, 0, 0,
		0, 0, 0,
		0, 0, 0,

		-1, -2, -1,
		-2, -4, -2,
		-1, -2, -1 };

	lightPosition = Vector3(0, 0, 0);
	lightIntensity = 1;
	ambient = 0.1;
}



vector<int> GradientShading::shadeVoxel(vector<float> voxelValues, vector<int> shadePosition) {
	float voxelColor = voxelValues[14] * 255;
	Vector3 view = Vector3(0, 0, 1);
	Vector3 shadePos = Vector3(shadePosition[0], shadePosition[1], shadePosition[2]);
	Vector3 lightDirection = lightPosition - shadePos;
	lightDirection.normalise();
	Vector3 H = (view + lightDirection);
	H.normalise();
	Vector3 gradient = Vector3(0, 0, 0);

	gradient[0] = convolute(voxelValues, xKernel);
	gradient[1] = convolute(voxelValues, yKernel);
	gradient[2] = convolute(voxelValues, zKernel);
	gradient.normalise();
	float angle = gradient.dot(lightDirection);
	float c = 0;
	if (angle > 0){
		c = ((lightIntensity*voxelColor)*(gradient.dot(lightDirection))) + ambient * 255;
	}

	int co = round(c);
	vector<int> retColor = { co, co, co };
	return retColor;
}


float GradientShading::convolute(vector<float> values, vector<int> kernel){
	float ret = 0;

	for (int i = 0; i < 27; i++){
		ret += values[i] * kernel[i];
	}
	return ret;
}

void GradientShading::SetLightIntensity(float i){
	lightIntensity = i;
}


GradientShading::~GradientShading()
{
}
