/**
 * \author George Brown
 *
 * \file PointLight.hpp 
 * \brief Light source with a specific position in space which emits light in all directions uniformly.
 *
 */

#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include "Math.hpp"
#include "Light.hpp"

/*! \class PointLight Class which defines a Point light, which has color wavelength data and a position in space */
class PointLight : public Light {
	
	public:
	
		/*! PointLight constructor
		 * \param pos_ The position of the point light in space
		 * \param rgb_ The color of the point light, in RGB */
		PointLight(Vec3f pos_, Vec3f rgb_);
		
		/*! Computes the L vector used in Phong illumination
		 * \param intersectPoint The point of intersection
		 * \return The L vector used in Phong illumination */
		Vec3f computeL(Vec3f intersectPoint_);
		
		/*! Determines whether the light is blocked by an object, with respect 
		 *  to a given position on another object's surface
		 *  \param objects_ Container of pointers to all the objects in the scene
		 *  \param thisObj_ Pointer to the object in question
		 *  \param surfacePos_ Position on the surface of the object in question
		 *  \return Boolean flag which is true if the light is blocked, false otherwise */
		bool isBlocked(const std::vector<Object*>& objects_, Object* thisObj_, Vec3f surfacePos_);
		
		/*! Gets the position of the point light
		 * \return The position of the point light */
		Vec3f getPos() const;
		
	private:
	
		Vec3f pos;
	
};

#endif

