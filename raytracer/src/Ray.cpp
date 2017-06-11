#include "Ray.hpp"

// Constructs the ray //
Ray::Ray(Vec3f origin_, Vec3f dir_){
	origin = origin_;
	dir = Vec3f::normalize(dir_);
}

Vec3f Ray::getOrigin() const {
	return origin;
}

Vec3f Ray::getDir() const {
	return dir;
}
