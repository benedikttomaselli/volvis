#include "VolumeRender.h"
#include "Volume.h"
#include "GradientShading.h"
using namespace std;



VolumeRender::VolumeRender(GradientShading* grad)
{
	gradient = grad;
}

VolumeRender::VolumeRender(){

}

//draws the volume
void VolumeRender::drawVolume(QImage* image, QLabel* label, bool invert, bool alt, int step, ViewDirection vd)
{
	image->fill(Qt::black);
	int xDim = 0;
	int yDim = 0;
	int zDim = 0;
	xDim = toDraw.width();
	yDim = toDraw.height();
	zDim = toDraw.depth();

	if (vd == TOP){
		xDim = toDraw.width(); //x
		yDim = toDraw.height(); //y
		zDim = toDraw.depth(); //z
	}
	else if (vd == SIDE){
		xDim = toDraw.width(); //x
		yDim = toDraw.depth(); //z
		zDim = toDraw.height(); //y
	}
	else if (vd == FRONT) {
		//	xDim = toDraw.depth(); //z
		//	yDim = toDraw.width(); //x
		//	zDim = toDraw.height(); //y

		xDim = toDraw.height(); //y
		yDim = toDraw.depth(); //z
		zDim = toDraw.width(); //x
	}


	int centerX = image->width() / 2;
	int centerY = image->height() / 2;
	for (int x = 0; x < xDim; x++){
		for (int y = 0; y < yDim; y++){
			vector<int> color = castRay(x, y, zDim, invert, alt, step, vd); //[0-2] are the rgb-values, [3] is the z-coord of the voxel			

			if (alt) {
				vector<int> shadePosition = { x, y, color[3] };
				vector<float> voxelValues = fillVoxelValues(x, y, color[3], xDim, yDim, zDim, vd);
				vector<int> set = gradient->shadeVoxel(voxelValues, shadePosition);
				QRgb setRgb = QRgb(qRgb(set[0], set[1], set[2]));
				image->setPixel(x + centerX - xDim / 2, y + centerY - yDim / 2, setRgb);
			}
			else {
				QRgb set = QRgb(qRgb(color[0], color[1], color[2]));
				image->setPixel(x + centerX - xDim / 2, y + centerY - yDim / 2, set);
				//	delete color;

			}
		}


	}
	label->setPixmap(QPixmap::fromImage(*image));
}

vector<float> VolumeRender::fillVoxelValues(int x, int y, int z, int xDim, int yDim, int zDim, ViewDirection vd){
	vector<float> ret;
	if (x - 1 >= 0 && x + 1 < xDim && y - 1 >= 0 && y + 1 < yDim && z - 1 >= 0 && z + 1 < zDim){

		ret = { getVoxelValue(x - 1, y - 1, z - 1, vd), getVoxelValue(x, y - 1, z - 1, vd), getVoxelValue(x + 1, y - 1, z - 1, vd),
			getVoxelValue(x - 1, y, z - 1, vd), getVoxelValue(x, y, z - 1, vd), getVoxelValue(x + 1, y, z - 1, vd),
			getVoxelValue(x - 1, y + 1, z - 1, vd), getVoxelValue(x, y + 1, z - 1, vd), getVoxelValue(x + 1, y + 1, z - 1, vd),

			getVoxelValue(x - 1, y - 1, z, vd), getVoxelValue(x, y - 1, z, vd), getVoxelValue(x + 1, y - 1, z, vd),
			getVoxelValue(x - 1, y, z, vd), getVoxelValue(x, y, z, vd), getVoxelValue(x + 1, y, z, vd),
			getVoxelValue(x - 1, y + 1, z, vd), getVoxelValue(x, y + 1, z, vd), getVoxelValue(x + 1, y + 1, z, vd),

			getVoxelValue(x - 1, y - 1, z + 1, vd), getVoxelValue(x, y - 1, z + 1, vd), getVoxelValue(x + 1, y - 1, z + 1, vd),
			getVoxelValue(x - 1, y, z + 1, vd), getVoxelValue(x, y, z + 1, vd), getVoxelValue(x + 1, y, z + 1, vd),
			getVoxelValue(x - 1, y + 1, z + 1, vd), getVoxelValue(x, y + 1, z + 1, vd), getVoxelValue(x + 1, y + 1, z + 1, vd) };
	}
	else {
		ret = { 0, 0, 0,
			0, 0, 0,
			0, 0, 0,
			0, 0, 0,
			0, 0, 0,
			0, 0, 0,
			0, 0, 0,
			0, 0, 0,
			0, 0, 0 };
	}
	return ret;
}

float VolumeRender::getVoxelValue(int x, int y, int z, ViewDirection vd){
	if (vd == TOP){
		return toDraw.voxel(x, y, z).getValue();
	}
	else if (vd == SIDE){
		return  toDraw.voxel(x, z, y).getValue();
	}
	else if (vd == FRONT) {
		return  toDraw.voxel(z, x, y).getValue();
	}
}

void VolumeRender::setVolume(const Volume &vol){
	toDraw = vol;
}

void VolumeRender::setLightIntensity(float i){
	gradient->SetLightIntensity(i);
}

void VolumeRender::setAmbientIntensity(float i){
	gradient->ambient = i;
}

VolumeRender::~VolumeRender()
{
	delete gradient;
}
