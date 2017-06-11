/**
 * \author George Brown
 *
 * \file Sphere.hpp 
 * \brief A special case of a perfectly round object, 
 *        fully specified by just a position and radius.
 *
 */

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Object.hpp"

/*! \class Sphere A sphere is an object derived from the base Object. 
 *  It has a position and radius */
class Sphere : public Object {
	
	public:
	
	
		/*! Sphere constructor
		 * \param pos_ The position of the sphere
		 * \param radius_ The radius of the sphere
		 * \param material_ The material of the sphere
		 * \param texture_ The texture to apply to the sphere (optional) */
		Sphere(Vec3f pos_, float radius_, Material* material_, Texture* texture_ = 0);
		
		/*! Determines whether a ray intersects the sphere. 
		 * \param ray The ray shot out by the raytracer
		 * \param rayPayload The associated payload data for the ray
		 * \return True if the ray intersects the sphere, false otherwise */
		bool intersect(Ray& ray, RayPayload& rayPayload);
		
		/*! Determines unit normal at a particular point on the surface of the sphere.
		 * \param pointOnSurface The point on the surface of the sphere in which to compute the normal.
		 * \return Unit surface normal at point on sphere */
		Vec3f getUnitSurfaceNormal(Vec3f pointOnSurface);
		
	private:
		
		/*! Position of the center of the sphere */
		Vec3f pos;
		
		/*! Radius of the sphere */
		float radius;
		
};
	

#endif
