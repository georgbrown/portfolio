#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight(Vec3f dir_, Vec3f rgb_)
	: Light(rgb_), dir(dir_) {
}

// Computes the L vector used in Phong illumination
Vec3f DirectionalLight::computeL(Vec3f intersectPoint_){
	return -1.f * dir;
}

// Determines whether the light is blocked by an object, with respect to a given position on another object's surface
bool DirectionalLight::isBlocked(const std::vector<Object*>& objects_, Object* thisObj_, Vec3f surfacePos_){

	Vec3f rayDir = -1.f * dir;

	Object* nearestObj = 0;
	float tmin = 1000000.f;

	Ray shadowRay(surfacePos_,rayDir);
	RayPayload rayPayload;

	for(int i = 0; i < objects_.size(); i++){
		if( (objects_[i] != thisObj_ ) && objects_[i]->intersect(shadowRay,rayPayload) ){
			rayPayload.setObject( objects_[i] );
		}
	}
	
	if( rayPayload.getObject() != 0 && rayPayload.getObject() != NULL ){
		return true;
	}
	
	return false;
	
}

/*! Returns the direction (a unit vector) of the directional light */
Vec3f DirectionalLight::getDir() const{
	return dir;
}






