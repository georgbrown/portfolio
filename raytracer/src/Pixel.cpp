#include "Pixel.hpp"

Pixel::Pixel(){
}

// RGB Getter //
Vec3f Pixel::getRgb() const{
	return Vec3f(r,g,b);
}

// RGB data set from an input 3d vector
void Pixel::setRgb(Vec3f rgb){
	r = rgb.x;
	g = rgb.y;
	b = rgb.z;
}

// RGB data set from three input floats
void Pixel::setRgb(float r_, float g_, float b_){
	r = r_;
	g = g_;
	b = b_;
}
