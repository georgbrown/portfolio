#include "Sphere.hpp"

Sphere::Sphere(Vec3f pos_, float radius_, Material* material_, Texture* texture_) 
	: Object(material_,texture_), pos(pos_), radius(radius_) {
}


// Determines whether a ray intersects the sphere. If so, returns a scalar t such that
// ray.origin + t * ray.dir is the position on the sphere where the intersection occurs
// Else, returns -1
bool Sphere::intersect(Ray& ray, RayPayload& rayPayload){
	
	Vec3f rayOrigin = ray.getOrigin();
	Vec3f rayDir = ray.getDir();
	
	float A = 1.f;
	float B = 2.0 * Vec3f::dot(rayDir, rayOrigin - pos );
	float C = powf((rayOrigin.x - pos.x),2.f) + powf((rayOrigin.y - pos.y),2.f) + powf((rayOrigin.z - pos.z),2.f) - radius*radius;
	
	float disc = B*B - 4.f*A*C;
	
	float t = -1;
	if( disc >= 0 ){
		float t1 = (-B + sqrt(disc)) / (2.0*A);
		float t2 = (-B - sqrt(disc)) / (2.0*A);
		
		if( t1 < t2 && t1 >= 0 ){
			t = t1;
		} else if( t2 < t1 && t2 >= 0 ){
			t = t2;
		}
	}
	
	if( t >= 0 && t < rayPayload.getDistance()){
		rayPayload.setMaterial(material);
		rayPayload.setDistance(t);
		
		if( texture != 0 && texture != NULL ){
		
			rayPayload.setTexture(texture);
		
			Vec3f pointOnSurface = rayOrigin + t * rayDir;
			
			float PI = 3.1415926535;
			float phi = acosf( (pointOnSurface.z - pos.z) / radius );
			float theta = atan2f( (pointOnSurface.y - pos.y) , (pointOnSurface.x - pos.x) );
			if( theta < 0 ){
				theta = theta + 2.f * PI;
			}

			float u = theta / (2.f*PI);
			float v = phi / PI;
		
			Vec2i texIndices = texture -> getIndices(u,v);
			rayPayload.setTextureColor( texture -> getPixelColor(texIndices) );
			
			
		} else {
			rayPayload.setTexture(0);
		}
		
		return true;
	}
	
	return false;
}

Vec3f Sphere::getUnitSurfaceNormal(Vec3f pointOnSurface){
	return Vec3f::normalize( pointOnSurface - pos );
}


