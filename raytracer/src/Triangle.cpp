#include "Triangle.hpp"

Triangle::Triangle(Vert* vert0_, Vert* vert1_, Vert* vert2_, Material* material_, Texture* texture_)
	: Object(material_,texture_) {
	
	normalsProvided = false;
	
	verts[0] = vert0_;
	verts[1] = vert1_;
	verts[2] = vert2_;
	
	Vec3f p0 = verts[0]->getPos();
	Vec3f p1 = verts[1]->getPos();
	Vec3f p2 = verts[2]->getPos();
	
	Vec3f e1 = p1 - p0;
	Vec3f e2 = p2 - p0;
	Vec3f n = Vec3f::cross(e1,e2);
	normal = Vec3f::normalize(n);
	
	A = n.x;
	B = n.y;
	C = n.z;
	D = -Vec3f::dot(n,verts[0]->getPos());
	
}

bool Triangle::intersect(Ray& ray, RayPayload& rayPayload){
	
	Vec3f rayOrigin = ray.getOrigin();
	Vec3f rayDir = ray.getDir();
	
	float numerator = -( A*rayOrigin.x + B*rayOrigin.y + C*rayOrigin.z + D );
	float denom = A*rayDir.x + B*rayDir.y + C*rayDir.z;
	
	if( fabs(denom) > 1.e-3 ){
		float distance = numerator / denom;
		if( distance > 0 && distance < rayPayload.getDistance() ){
			
			Vec3f p = rayOrigin + distance * rayDir;
			bool inside = isInside(p);
			
			if( inside ){
				rayPayload.setDistance(distance);
				rayPayload.setMaterial(material);
				
				if( texture != 0 && texture != NULL ){
					
					rayPayload.setTexture(texture);
					
					Vec2f vt1 = verts[0]->getTextureCoords();
					Vec2f vt2 = verts[1]->getTextureCoords();
					Vec2f vt3 = verts[2]->getTextureCoords();
					Vec3f baries = getBarycentricCoords(p);
					float u = baries.x*vt1.x + baries.y*vt2.x + baries.z*vt3.x;
					float v = baries.x*vt1.y + baries.y*vt2.y + baries.z*vt3.y;
					Vec2i texIndices = texture -> getIndices(u,v);
					rayPayload.setTextureColor( texture -> getPixelColor(texIndices) );
				
				} else {
					rayPayload.setTexture(0);
				}
				
				return true;
			}
		}
	}
	
	return false;

}

Vec3f Triangle::getUnitSurfaceNormal(Vec3f pointOnSurface){
	
	if( !isInside(pointOnSurface) ){
		std::cout << "Error: Point is not inside the triangle, so cannot compute unit surface normal.\n";
		exit(0);
	}
	
	if( normalsProvided ){
		Vec3f baries = getBarycentricCoords(pointOnSurface);
		return Vec3f::normalize( baries.x*verts[0]->getNormal() + 
		                         baries.y*verts[1]->getNormal() + 
		                         baries.z*verts[2]->getNormal() );
	} else {
		return normal;
	}
	
}

Vec3f Triangle::getBarycentricCoords(Vec3f point){
	
	Vec3f p0 = verts[0]->getPos();
	Vec3f p1 = verts[1]->getPos();
	Vec3f p2 = verts[2]->getPos();
			
	Vec3f e1 = p1 - p0;
	Vec3f e2 = p2 - p0;
	Vec3f e3 = point - p1;
	Vec3f e4 = point - p2;
			
	float area = 0.5 * Vec3f::norm( Vec3f::cross( e1,e2) );
	float a = 0.5 * Vec3f::norm( Vec3f::cross( e3,e4 ) );
	float b = 0.5 * Vec3f::norm( Vec3f::cross( e4,e2 ) );
	float c = 0.5 * Vec3f::norm( Vec3f::cross( e1,e3 ) );
			
	float alpha = a / area;
	float beta = b / area;
	float gamma = c / area;
	
	return Vec3f(alpha,beta,gamma);
	
}

bool Triangle::isInside(Vec3f point){
	
	Vec3f baries = getBarycentricCoords(point);
	return ( baries.x + baries.y + baries.z - 1.f < 1.e-3 );
	
}

void Triangle::setNormalsProvided(bool normalsProvided_){
	normalsProvided_ = normalsProvided;
}
