/**
 * \author George Brown
 *
 * \file Image.hpp 
 * \brief The final image produced by the raytracer program is an array of pixels.
 *        Functionality is provided for drawing an image of a given scene with viewing
 *        window parameters, and for saving the pixel array to a PPM file.
 */

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include <tuple>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Math.hpp"
#include "Pixel.hpp"
#include "Scene.hpp"
#include "Window.hpp"
#include "Ray.hpp"

/*! \class Image Class which defines an image which is drawn from casting rays through a 3D scene
 The image contains an array of pixels */ 
class Image {
	
	public:
	
		/*! Image constructor.
		 *  \param dims The dimensions of the image, a 2d vector of ints corresponding to
		 *         the number of pixels for the width and height of the image */
		Image(Vec2i dims);
		
		
		/*! Draw an image of the current scene with the current window information to yield
		 *  an array of pixel data
		 *  \param scene The scene which contains all the objects and environment data.
		 *  \param window The window through which the scene is viewed */
		void draw(Scene scene, Window window);
		
		
		/*! Saves the pixel array data to a PPM file to be viewed by an external program
		 *  \param filename The name of the file to save the data to. */
		void saveToPpm(const std::string& filename);
	
	private:
	
		/*! 2D-array of pixels for the image */
		std::vector< std::vector<Pixel> > pixels;
		
		/*! Image width */
		int width;
		
		/*! Image height */
		int height;
	
};

#endif

