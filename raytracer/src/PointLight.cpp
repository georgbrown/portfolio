#include "PointLight.hpp"

PointLight::PointLight(Vec3f pos_, Vec3f rgb_)
	: Light(rgb_), pos(pos_) {
}

// Computes the L vector used in Phong illumination
Vec3f PointLight::computeL(Vec3f intersectPoint_){
	return Vec3f::normalize( pos - intersectPoint_ );
}


// Determines whether the light is blocked by an object, with respect to a given position on another object's surface
bool PointLight::isBlocked(const std::vector<Object*>& objects_, Object* thisObj_, Vec3f surfacePos_){
	
	Vec3f rayDir = Vec3f::normalize(pos - surfacePos_);
	float lightDist = Vec3f::norm(pos - surfacePos_);

	Object* nearestObj = 0;
	float tmin = 1000000.f;

	Ray shadowRay(surfacePos_,rayDir);
	RayPayload rayPayload;

	for(int i = 0; i < objects_.size(); i++){
		if( (objects_[i] != thisObj_) && objects_[i]->intersect(shadowRay,rayPayload) ){
			if( rayPayload.getDistance() > 0.005 ){
				rayPayload.setObject( objects_[i] );
			}
		}
	}
	
	if( rayPayload.getObject() != 0 && rayPayload.getObject() != NULL ){
		
		return true;
	}
	
	return false;
	
}

Vec3f PointLight::getPos() const{
	return pos;
}


