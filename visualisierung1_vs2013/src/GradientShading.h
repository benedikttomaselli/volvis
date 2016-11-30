#pragma once
#include <vector>
#include "Vector.h"

using namespace std;

class GradientShading
{
public:
	GradientShading();
	~GradientShading();

	vector<int> shadeVoxel(vector<float> voxelValues, vector<int> shadePosition);
	vector<float> calculateGradient(vector<float> voxelValues);
	//	float convolute(vector<float> values, vector<int> kernel);
	void SetLightIntensity(float i);

	Vector3 lightPosition;
	float lightIntensity;
	float ambient;


private:

	vector<int> xKernel;
	vector<int> yKernel;
	vector<int> zKernel;


	float convolute(vector<float> values, vector<int> kernel);
	vector<float> vec3Sub(vector<int> a, vector<int> b);
};

