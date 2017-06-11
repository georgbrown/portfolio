#include "Light.hpp"

Light::Light(Vec3f rgb_){

	if( rgb_.x < 0.f || rgb_.x > 1.f || rgb_.y < 0.f || rgb_.y > 1.f || rgb_.z < 0.f || rgb_.z > 1.f ){
		std::cout << "Error: The specified RGB color values for the 'light' are invalid. Each value must\n";
		std::cout << "be a floating point number in the range 0-1.\n";
		exit(0);
	}

	rgb = rgb_;
}

Vec3f Light::getRGB() const{
	return rgb;
}
