#include "Image.hpp"

Image::Image(Vec2i dims){
	const int pixw = dims.x;
	const int pixh = dims.y;
	
	pixels.resize(pixh);
	for(int j = 0; j < pixels.size(); j++){
		pixels[j].resize(pixw);  
	}
	
}


void Image::draw(Scene scene, Window window){
	
	const int pixw = pixels.size();
	const int pixh = pixels[0].size();
	
	for(int i = 0; i < pixels.size(); i++){
		for(int j = 0; j < pixels[i].size(); j++) {
			
			Vec3f origin = scene.getEyePos();
			Vec3f windowCoords = window.pixelToWindow(Vec2i(j,i));
			Vec3f viewDir = Vec3f::normalize(windowCoords - origin);
			
			Ray ray(origin,viewDir);
			RayPayload rayPayload;
			
			scene.traceRay(ray,rayPayload);
			
			Vec3f colors;
			if( rayPayload.getMaterial() != 0 && rayPayload.getMaterial() != NULL ){
				colors = scene.shadeRay(ray,rayPayload);
			} else {
				colors = scene.getBkgColor();
			}
			
			pixels[i][j].setRgb(colors);
			
		}
	}

}



void Image::saveToPpm(const std::string& filename){
	
	std::cout << "Output file: " << filename << std::endl;
	
	std::ofstream outputfile( filename.c_str() );
	
	if( outputfile.is_open() ){
		
		int width = pixels[0].size();
		int height = pixels.size();
		
		// The standard ppm format.
		std::stringstream ss( std::string("") );
		ss << "P3\n";
		ss << "# ppm data for an image with a given width, height, and pixel values from 0-255 \n";
		ss << width << " " << height << std::endl;
		ss << 255 << std::endl;
		
		// Looping through the image data and writing the rgb values.  Each pixel gets its own line.
		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				Vec3f rgb = pixels[i][j].getRgb();
					ss << int(255.f*rgb.x) << " "
					   << int(255.f*rgb.y) << " "
					   << int(255.f*rgb.z) << std::endl;
			}
		}
		

		outputfile << ss.rdbuf();
		
	} else {
		std::cout << "Error: Failed to open an output file with the given filename.\n";
		exit(0);
	}
	
}
