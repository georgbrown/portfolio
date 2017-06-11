/**
 * \author George Brown
 *
 * \file main.cpp
 * \brief Main application file. The scene data is parsed from a configuration file.
 *        A viewing window is constructed, and the scene is viewed through the window
 *        and drawn to an image using raytracing. The final output image is saved to file
 *        as a PPM.
 */

//	To run this example, pass a text file as an argument.
//	e.g. "./raytracer ../scene.txt"
//


#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <utility>
#include <string>
#include <vector>
#include <tuple>


#include "Math.hpp"
#include "Image.hpp"
#include "Scene.hpp"
#include "Parser.hpp"
#include "Object.hpp"
#include "Sphere.hpp"
#include "Window.hpp"


int main( int argc, char **argv ){

	// Parsing input to extract the scene data
	Scene scene = Parser::parse(argc,argv);
	
	// Printing parsed scene data to terminal
	scene.printData();
	
	// Constructing the viewing window
	Window window(scene);
	
	// Creating a blank canvas
	Image image(scene.getEnvDims());
	
	// Drawing the image using ray tracing
	image.draw(scene,window);
	
	// Saving the image to file in PPM format
	std::string outputFilename = scene.getSceneName() + ".ppm";
	image.saveToPpm(outputFilename);

	return 0;

} // end main

