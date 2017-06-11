/**
 * \author George Brown
 *
 * \file Texture.hpp 
 * \brief Textures may be applied to objects to add interesting patterns and designs.
 *        Textures are loaded from reference images and mapped to the surface of objects.
 */

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <vector>
#include <tuple>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Math.hpp"
#include "Pixel.hpp"

/*! \class Texture Texture class, with methods for loading textures and mapping to objects */
class Texture {
	
	public:
	
		/*! Texture constructor */
		Texture();
		
		/*! Loads a texture file with a PPM image format
		 * \param filename The name of the texture file to load */
		void loadFromPpm(const std::string& filename);
		
		/*! Gets pixel coordinates mapped to by (u,v) texture coordinates
		 * \param u The texture coordinate along the width of the image [0,1]
		 * \param v The texture coordinate along the height of the image [0,1]
		 * \return Pixel coordinates corresponding to the texture coordinates */
		Vec2i getIndices(float u, float v);
		
		/*! Gets the color of the pixel at the specified pixel coordinates
		 * \param indices The pixel coordinates 
		 * \return The RGB color of the pixel at the specified coordinates */
		Vec3f getPixelColor(Vec2i indices);
		
	private:
	
		/*! Texture image width, in pixels */
		int width;
		
		/*! Texture image height, in pixels */
		int height;
		
		/*! 2D array of pixels representing the texture image */
		std::vector< std::vector<Pixel> > pixels;
	
};

#endif





