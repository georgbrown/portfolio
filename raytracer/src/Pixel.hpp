/**
 * \author George Brown
 *
 * \file Pixel.hpp 
 * \brief A pixel is the fundamental building block in an image. The image is
 *        a 2D array of pixels, each with its own color specified in RGB format.
 */

#ifndef PIXEL_HPP
#define PIXEL_HPP

#include "Math.hpp"

/*! \class Pixel Class which stores the color data for an individual pixel. 
 * r, g, and b represent red, green, and blue amounts respectively.
 * Colors are stored as floats and range between 0 - 1. */
class Pixel {
	
	public:
	
		/*! Pixel Constructor */
		Pixel();
		
		/*! Gets the RGB data and returns it as a 3D vector of floats
		 * \return Color as an RGB tuple */
		Vec3f getRgb() const;
		
		/*! Sets the RGB color data from a 3D vector
		 * \param rgb A 3D vector of floats corresponding to the RGB values */
		void setRgb(Vec3f rgb);
		
		/*! Sets the RGB color data from individual color component inputs
		 * \param r The red component
		 * \param g The green component
		 * \param b The blue component */
		void setRgb(float r_, float g_, float b_);
		
	private:

		/*! Red */
		float r;
		
		/*! Green */
		float g;   
		
		/*! Blue */
		float b;
	
};

#endif
