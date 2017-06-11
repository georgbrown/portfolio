/**
 * \author George Brown
 *
 * \file Ray.hpp 
 * \brief The raytracer shoots rays across the scene starting from the view origin.
 *        Every ray has an origin and a direction of travel. Data about possible collisions
 *        with objects in the scene is also relevant, but is stored separately in a RayPayload object.
 */

#ifndef RAY_HPP
#define RAY_HPP

#include "Math.hpp"
#include <iostream>

/*! \class Ray Class which defines a ray, which emanates from some origin position and shoots in some specified direction */
class Ray {
	
	public:
	
		/*! Constructs the ray with the origin and direction
		 * \param origin_ The origin of the ray
		 * \param dir_ The direction the ray travels in */
		Ray(Vec3f origin_, Vec3f dir_);
	
		/*! Getter for the ray origin
		 * \return The origin of the ray */
		Vec3f getOrigin() const;
		
		/*! Getter for the ray direction
		 * \return The direction the ray travels in */
		Vec3f getDir() const;
	
	private:
	
		/*! Starting position of the ray */
		Vec3f origin;
		
		/*! Direction the ray travels in */
		Vec3f dir;
	
};

#endif
