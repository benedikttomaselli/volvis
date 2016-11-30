//Kolb Mathias, 0625588
//Tomaselli Benedikt, 0926048

#include "VR.h"
#include "Volume.h"
#include "Shading.h"
using namespace std;



VR::VR(Shading* shading)
{
	shading = shading;
}

VR::VR(){

}

//draws the volume
void VR::drawVolume(QImage* image, QLabel* label, bool invert, bool alt, int step, ViewDirection vd)
{
	//set the dimensions of the volume to draw
	image->fill(Qt::black);
	int xDim = 0;
	int yDim = 0;
	int zDim = 0;
	xDim = toDraw.width();
	yDim = toDraw.height();
	zDim = toDraw.depth();

	//switch dimensions depending on the point of view
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
		xDim = toDraw.height(); //y
		yDim = toDraw.depth(); //z
		zDim = toDraw.width(); //x
	}

	//find the center of the image
	int centerX = image->width() / 2;
	int centerY = image->height() / 2;
	for (int x = 0; x < xDim; x++){
		for (int y = 0; y < yDim; y++){
			//Cast rays through the image in z-direction for each pixel on the xy-plane (view direction)
			vector<int> color = castRay(x, y, zDim, invert, alt, step, vd); //RGB values are (0-2), Z-Coordinate of the voxel is (3)		
			if (alt) {		//if shading was selected, then:
				vector<int> shadePosition = { x, y, color[3] };
				vector<float> voxelValues = fillVoxelValues(x, y, color[3], xDim, yDim, zDim, vd);
				vector<int> set = shading->shadeVoxel(voxelValues, shadePosition);
				QRgb setRgb = QRgb(qRgb(set[0], set[1], set[2]));
				image->setPixel(x + centerX - xDim / 2, y + centerY - yDim / 2, setRgb);
			}		
			else {		//if shading was not selected, the color gets removed
				QRgb set = QRgb(qRgb(color[0], color[1], color[2]));
				image->setPixel(x + centerX - xDim / 2, y + centerY - yDim / 2, set);
				//	delete color;

			}
		}
	}
	label->setPixmap(QPixmap::fromImage(*image));
}

vector<float> VR::fillVoxelValues(int x, int y, int z, int xDim, int yDim, int zDim, ViewDirection vd){
	vector<float> ret;
	if (x - 1 >= 0 && x + 1 < xDim && y - 1 >= 0 && y + 1 < yDim && z - 1 >= 0 && z + 1 < zDim){		//check if coordinates are still within the object
		//if yes, fill vector with voxel values
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
	else {		//if not, fill vector with zeros
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

float VR::getVoxelValue(int x, int y, int z, ViewDirection vd){
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

void VR::setVolume(const Volume &vol){
	toDraw = vol;
}

void VR::setLightIntensity(float i){
	shading->SetLightIntensity(i);
}

void VR::setAmbientIntensity(float i){
	shading->ambient = i;
}

VR::~VR()
{
	delete shading;
}
