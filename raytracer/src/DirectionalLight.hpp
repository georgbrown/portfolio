/**
 * \author George Brown
 *
 * \file DirectionalLight.hpp
 * \brief Light source with a uniform direction and no source position. Like a point
 *        source with infinite distance from the target.
 */

#ifndef DIRECTIONAL_LIGHT_HPP
#define DIRECTIONAL_LIGHT_HPP

#include "Math.hpp"
#include "Light.hpp"

/*! \class DirectionalLight Class which defines a Directional light, which has 
 *  color wavelength data and a direction */
class DirectionalLight : public Light {
	
	public:
	
		/*! DirectionalLight Constructor 
		 *  \param dir_ A unit vector pointing in the direction of the light.
		 *  \param rgb_ The RGB color values for the light source source. */ 
		DirectionalLight(Vec3f dir_, Vec3f rgb_);
		
		/*! Computes the L vector used in Phong illumination
		 *  \param intersectPoint_ The spatial point in which the light source is intersecting the object
		 *  \return The L vector used in Phong illumination */
		Vec3f computeL(Vec3f intersectPoint_);
		
		/*! Determines whether the light is blocked by an object, with respect 
		 *  to a given position on another object's surface
		 *  \param objects_ Container of pointers to all the objects in the scene
		 *  \param thisObj_ Pointer to the object in question
		 *  \param surfacePos_ Position on the surface of the object in question
		 *  \return Boolean flag which is true if the light is blocked, false otherwise. */
		bool isBlocked(const std::vector<Object*>& objects_, Object* thisObj_, Vec3f surfacePos_);
		
		/*! Gets the direction of the directional light
		 *  \return A unit vector pointing in the direction of the directional light */
		Vec3f getDir() const;
		
	private:
	
		/*! The direction of the directional light */
		Vec3f dir;
	
};

#endif
