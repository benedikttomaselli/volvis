#pragma once
#include <vector>
#include "Volume.h"
#include <QColor>
#include <QPainter>
#include <QLabel>
#include <QRgb>
#include "Shading.h"



using namespace std;

class VR
{
public:
	VR(Shading* shading);
	VR();
	~VR();

	enum ViewDirection{
		TOP = 0,
		SIDE = 1,
		FRONT = 2,
	};

	virtual void drawVolume(QImage* image, QLabel* label, bool invert, bool alt, int step, ViewDirection vd);
	virtual  vector<int> castRay(int x, int y, int zDim, bool invert, bool alt, int step, ViewDirection vd) = 0;
	void setVolume(const Volume &vol);
	void setLightIntensity(float i);
	void setAmbientIntensity(float i);

protected:
	Volume toDraw;
	float getVoxelValue(int x, int y, int z, ViewDirection vd);
	Shading* shading;
	vector<float> fillVoxelValues(int x, int y, int z, int xDim, int yDim, int zDim, ViewDirection vd);
};

class VR_MIP :
	public VR
{
public:
	vector<int> castRay(int x, int y, int zDim, bool invert, bool alt, int step, ViewDirection vd) override;
	VR_MIP(Shading* shading);
	~VR_MIP();
};

class VR_AlphaCompositing :
	public VR

{
public:
	vector<int> castRay(int x, int y, int zDim, bool invert, bool alt, int step, ViewDirection vd) override;
	VR_AlphaCompositing(Shading* shading);
	~VR_AlphaCompositing();
private:
	vector<int> transfer(float value, bool invert);
	vector<int> Over(vector<int> a, vector<int> b, float alpha);
};

class VR_FirstHit :
	public VR
{
public:
	vector<int> castRay(int x, int y, int zDim, bool invert, bool alt, int step, ViewDirection vd) override;
	VR_FirstHit(Shading* shading);
	~VR_FirstHit();
	void setThreshold(float t);

private:
	float threshold;
};



