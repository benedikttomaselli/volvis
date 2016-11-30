#pragma once
#include <vector>
#include "Volume.h"
#include <QColor>
#include <QPainter>
#include <QLabel>
#include <QRgb>
#include "GradientShading.h"



using namespace std;

class VolumeRender
{
public:
	VolumeRender(GradientShading* grad);
	VolumeRender();
	~VolumeRender();

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
	GradientShading* gradient;
	vector<float> fillVoxelValues(int x, int y, int z, int xDim, int yDim, int zDim, ViewDirection vd);
};

class VolumeRenderMIP :
	public VolumeRender
{
public:
	vector<int> castRay(int x, int y, int zDim, bool invert, bool alt, int step, ViewDirection vd) override;
	VolumeRenderMIP(GradientShading* grad);
	~VolumeRenderMIP();
};

class VolumeRenderAlphaComp :
	public VolumeRender

{
public:
	vector<int> castRay(int x, int y, int zDim, bool invert, bool alt, int step, ViewDirection vd) override;
	VolumeRenderAlphaComp(GradientShading* grad);
	~VolumeRenderAlphaComp();
private:
	vector<int> transfer(float value, bool invert);
	vector<int> Over(vector<int> a, vector<int> b, float alpha);
};

class VolumeRenderFirstHit :
	public VolumeRender
{
public:
	vector<int> castRay(int x, int y, int zDim, bool invert, bool alt, int step, ViewDirection vd) override;
	VolumeRenderFirstHit(GradientShading* grad);
	~VolumeRenderFirstHit();
	void setThreshold(float t);

private:
	float threshold;
};



