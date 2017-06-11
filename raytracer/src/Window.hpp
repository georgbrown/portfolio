/**
 * \author George Brown
 *
 * \file Window.hpp 
 * \brief The viewing window which the scene is observed through, and 
 *        controls the final image produced by the raytracer.
 */

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Math.hpp"
#include "Scene.hpp"
#include <iostream>

/*! \class Window Class which defines the viewing window */
class Window {
	
	public:
	
		/*! Window constructor
		 * \param scene The environment with all the entities that the viewing window observes */
		Window(Scene scene);
		
		/*! Maps pixel coordinates to 3D spatial coordinates
		 * \param pixelCoordinates The pixel coordinates in an image
		 * \return 3D spatial coordinates in the viewing window plane */
		Vec3f pixelToWindow(Vec2i pixelCoords);
	
	private:
	
		/*! Eye position */
		Vec3f origin;
		
		/*! Viewing direction */
		Vec3f view;
		
		/*! Up vector */
		Vec3f up;
		
		/*! Vertical field of view */
		float fovv;
		
		/*! Viewing window coordinate along the width */
		Vec3f u;
		
		/*! Viewing window coordinate along the height */
		Vec3f v;
		
		/*! Coordinates of the upper-left corner of viewing window */
		Vec3f ul;
		
		/*! Coordinates of the upper-right corner of viewing window */
		Vec3f ur;
		
		/*! Coordinates of the lower-left corner of viewing window */
		Vec3f ll;
		
		/*! Coordinates of the lower-right corner of viewing window */
		Vec3f lr;
		
		/*! Distance from viewing window to origin */
		float d;
		
		/*! Height of the viewing window */
		float h;
		
		/*! Width of the viewing window */
		float w;
		
		/*! Aspect ratio */
		float aspect;
		
		/*! Step size along horizontal direction */
		Vec3f dh;
		
		/*! Step size along vertical direction */
		Vec3f dv;
	
};

#endif
