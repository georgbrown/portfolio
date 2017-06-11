#include "Material.hpp"
#include <iostream>

Material::Material(){
}

	
Vec3f Material::getOd() const {
	return Od;
}
		
Vec3f Material::getOs() const {
	return Os;
}
		
float Material::getKa() const {
	return ka;
}
		
float Material::getKd() const {
	return kd;
}
	
float Material::getKs() const {
	return ks;
}
		
float Material::getN() const {
	return n;
}


void Material::setOd( Vec3f Od_ ){
	
	if( Od_.x < 0.f || Od_.x > 1.f || Od_.y < 0.f || Od_.y > 1.f || Od_.z < 0.f || Od_.z > 1.f ){
		std::cout << "Error: Material parameter 'Od' must be a vector of 3 floats with values ranging from 0-1.\n";
		exit(0);
	}
	
	Od = Od_;
}

void Material::setOs( Vec3f Os_ ){
	
	if( Os_.x < 0.f || Os_.x > 1.f || Os_.y < 0.f || Os_.y > 1.f || Os_.z < 0.f || Os_.z > 1.f ){
		std::cout << "Error: Material parameter 'Os' must be a vector of 3 floats with values ranging from 0-1.\n";
		exit(0);
	}
	
	Os = Os_;
}

void Material::setKa( float ka_ ){
	
	if( ka_ < 0.f || ka_ > 1.f ){
		std::cout << "Error: Material parameter 'ka' must be a float value between 0 and 1.\n";
		exit(0);
	}
	ka = ka_;
}

void Material::setKd( float kd_ ){
	
	if( kd_ < 0.f || kd_ > 1.f ){
		std::cout << "Error: Material parameter 'kd' must be a float value between 0 and 1.\n";
		exit(0);
	}
	
	kd = kd_;
}

void Material::setKs( float ks_ ){
	
	if( ks_ < 0.f || ks_ > 1.f ){
		std::cout << "Error: Material parameter 'ks' must be a float value between 0 and 1.\n";
		exit(0);
	}
	
	ks = ks_;
}

void Material::setN( float n_ ){
	
	if( n < 0 ){
		std::cout << "Error: Material parameter 'n' must be a nonnegative float value \n";
		exit(0);
	}
	
	n = n_;
}
