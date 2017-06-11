#include "Texture.hpp"

Texture::Texture(){
	width = -1;
	height = -1;
}


void Texture::loadFromPpm(const std::string& filename){
	
	std::string filepath = "../" + filename;
	std::ifstream inputfile( filepath.c_str() );
	
	if( inputfile.is_open() ){
		
		std::string headerLine="";
		std::getline( inputfile, headerLine );
		
		std::string header;
		int rgbMax;
		
		std::stringstream ss(headerLine);
		ss >> header >> width >> height >> rgbMax;
		
		pixels.resize(height);
		for(int i = 0; i < height; i++){
			pixels[i].resize(width);
			for(int j = 0; j < width; j++){
				
				std::string line;
				std::getline( inputfile, line );
				std::stringstream linestream(line);
				
				
				int r=-1, g=-1, b=-1;
				linestream >> r >> g >> b;
			
				if( r < 0 || r > rgbMax || g < 0 || g > rgbMax || b < 0 || b > rgbMax ){
					std::cout << "Error: In Texture ppm file, a line contains a tuple of RGB data which is not within the allowed bounds. \n";
					exit(0);
				}
			
				pixels[i][j].setRgb(r/255.f,g/255.f,b/255.f);
				
			}
		}
		
		
		
	} else {
		std::cout << "Error: Failed to open the input file with the given filename. \n";
		exit(0);
	}
	
}


Vec2i Texture::getIndices(float u, float v){

	if( width < 0 || height < 0 ){
		std::cout << "Error: width and height data not yet set, cannot grab indices into array.\n";
		exit(0);
	}

	int j = std::roundf( u * (width-1) );
	int i = std::roundf( v * (height-1) );
	
	return Vec2i(i,j);
	
}

Vec3f Texture::getPixelColor(Vec2i indices){

	return pixels[indices.x][indices.y].getRgb();
	
}
