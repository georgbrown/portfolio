/**
 * \author George Brown
 *
 * \file Light.hpp 
 * \brief Lights are used to illuminate the scene from different angles and positions. 
 */

#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <vector>
#include "Math.hpp"
#include "Object.hpp"
#include "Ray.hpp"

/*! \class Light Base class from which all types of lights are derived. Every light has color wavelength data, which is stored in the base class.
 This class also provides a virtual interface, requiring all classes inheriting from it to provide functions for computing L
 and determining whether the light is blocked by an object in the scene */
class Light {
	
	public:
	
		/*! Light constructor
		 *  \param rgb_ The RGB color values for the newly created light */
		Light(Vec3f rgb_);
		
		/*! Computes the L vector used in Phong illumination
		 *  \param intersectPoint_ The point where the light ray intersects a given object
		 *  \return The L vector used in Phong illumination */
		virtual Vec3f computeL(Vec3f intersectPoint_) = 0;
		
		/*! Determines whether the light is blocked by an object, 
		 *  with respect to a given position on another object's surface
		 *  \param objects_ A vector of pointers to all the objects in the scene
		 *  \param thisObj_ A pointer to the object in question whose surface the ray is at
		 *  \param surfacePos_ The point on the surface of the object
		 *  \return Boolean flag which is true if the light is blocked, false otherwise. */
		virtual bool isBlocked(const std::vector<Object*>& objects_, Object* thisObj_, Vec3f surfacePos_) = 0;
		
		/*! Gets the RGB color data
		 * \return The RGB color data as a 3D float vector */
		Vec3f getRGB() const;
		
	private:
	
		Vec3f rgb;
	
};

#endif
