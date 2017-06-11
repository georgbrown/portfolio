#include "Parser.hpp"
#include <iostream>

Parser::Parser(){
}

// Parses command arguments and produces a scene
Scene Parser::parse(int argc, char** argv){
	
	Scene scene;
	
	//	// Make sure the user specified an input file. If not, tell them how to do so.
	if( argc < 2 ){ 
		std::cerr << "**Error: you must specify an input file, " 
		<< "e.g. \"./example ../examplefile.txt\"" << std::endl; 
		exit(0); 
	}
	
	// Get the input text file, which should be the second argument.
	std::string filename( argv[1] );
	std::cout << "Input file: " << filename << std::endl;
	scene.setSceneName( removeSuffix(filename) );

	// Create a filestream for reading the text file, and open it.
	// The is_open call will return false if there was a problem.
	std::ifstream inputfile( filename.c_str() );
	if( inputfile.is_open() ){

		// Default material color is black. This is a state variable which defines the color for all objects created
		// until it is overwritten by a new material color definition
		
		Material* material = 0;
		Texture* texture = 0;
				
		//Vec3f mtlColor = Vec3f(0,0,0);

		// Use std::getline to parse the text file one line at a time.
		std::string line="";
		while( std::getline( inputfile, line ) ){

			// At this point, "line" contains the full text of the parsed line.
			// We can use a stringstream to parse out the space-delimited contents of the line
			std::stringstream ss( line );

			// Using the stream operator, get the first string of the line.
			// It will decide how we parse the rest of it.
			std::string var="";
			ss >> var;

			// Eye position
			if( var == "eye" ){
				Vec3f pos = parseVec3f(var,ss);
				scene.setEyePos( pos );
			}
			
			// Viewing direction vector
			else if( var == "viewdir" ){
				Vec3f viewDir = parseVec3f(var,ss);
				if( Vec3f::dot(viewDir,viewDir) < 1.e-6 ){
					std::cout << "Error: viewdir is too close to 0 magnitude. Please specify a unit vector.\n";
					exit(0);
				}
				viewDir = Vec3f::normalize( viewDir );
				scene.setViewDir( viewDir );
			}
			
			// The "Up" direction
			else if( var == "updir" ){
				Vec3f upDir = parseVec3f(var,ss);
				if( Vec3f::dot(upDir,upDir) < 1.e-6 ){
					std::cout << "Error: updir is too close to 0 magnitude. Please specify a unit vector.\n";
					exit(0);
				}
				upDir = Vec3f::normalize( upDir );
				scene.setUpDir( upDir );
			}
			
			// Field of view in vertical direction, in degrees
			else if( var == "fovv" ){
				float fovv = parseFloat(var,ss);
				
				if( fovv < 0  || fovv >= 180.f ){
					std::cout << "Error: fovv was outside of the acceptable range. Please choose a value larger than 0 and less than 180\n";
					exit(0);
				}
				
				scene.setFovv( fovv );
			}
			
			// The width and height of the image
			else if( var == "imsize" ){
				Vec2i imSize = parseVec2i(var,ss);
				scene.setEnvDims( imSize );
			}
			
			// Background color
			else if( var == "bkgcolor" ){
				Vec3f bkgColor = parseVec3f(var,ss);
				scene.setBkgColor( bkgColor );
			}
			
			// Material color state variable
			else if( var == "mtlcolor" ){

				float Odr, Odg, Odb;
				float Osr, Osg, Osb;
				float ka, kd, ks, n;
				
				ss >> Odr >> Odg >> Odb >> Osr >> Osg >> Osb >> ka >> kd >> ks >> n;
				
				material = new Material();
				material->setOd( Vec3f(Odr,Odg,Odb) );
				material->setOs( Vec3f(Osr,Osg,Osb) );
				material->setKa( ka );
				material->setKd( kd );
				material->setKs( ks );
				material->setN( n );
				
			}
			
			else if( var == "texture" ){
				
				std::string textureFilename;
				ss >> textureFilename;
				texture = new Texture();
				texture->loadFromPpm(textureFilename);
				
			}
			
			// Sphere data
			else if( var == "sphere" ){
				float x=0.f, y = 0.f, z = 0.f, r =0.f;
				ss >> x >> y >> z >> r;
				Vec3f pos(x,y,z);
				Sphere* sphere = new Sphere( pos, r, material, texture);
				scene.addObject( sphere );
				texture = 0;
			}
			
			else if( var == "light" ){
			
				float x=0.f, y=0.f, z=0.f;
				int w = 0;
				float r = 0.f, g = 0.f, b = 0.f;
				
				ss >> x >> y >> z >> w >> r >> g >> b;
				
				if( w == 1 ){
					scene.addPointLight( new PointLight( Vec3f(x,y,z) , Vec3f(r,g,b) ) );
				} else if( w == 0 ){
					Vec3f dir = Vec3f::normalize( Vec3f(x,y,z) );
					scene.addDirectionalLight( new DirectionalLight( dir , Vec3f(r,g,b) ) );
				} else {
					std::cout << "Error: Did not correctly specify the type of light. \n";
					std::cout << "Set the 'w' parameter to 0 for a point light, or 1 for a directional light.\n";
					exit(0);
				}
			
			}
			
			else if( var == "v" ){
				Vec3f pos = parseVec3f(var,ss);
				scene.addVert(pos);
			}
			
			else if( var == "vt" ){
				Vec2f coords = parseVec2f(var,ss);
				scene.addTextureCoords( coords );
			}
			
			else if( var == "vn" ){
				Vec3f normal = parseVec3f(var,ss);
				scene.addNormal( normal );
			}
			
			else if( var == "f" ){
				
				Vec3i v1;
				Vec3i v2;
				Vec3i v3;
				parseFace(v1,v2,v3,ss);
				scene.addTriangle(v1,v2,v3,material,texture);
				
			}
			
			// If it's a comment, don't do anything.
			else if( var[0] == '#' ){}

			else if( var == "" ){}

			// Otherwise, it's an error!
			else {
				std::cout << "Error: Invalid data found in config file.\n";
				std::cout << "Found var .. \"" << var << "\"\n";
				exit(0);	
			}

		} // end parse line

	}
	else { std::cerr << "**Error: Could not open file " << filename << std::endl; exit(0); }
	
	
	
	
	// Before returning the scene, we must check to make sure the viewing direction and up direction are not parallel
	float dot = Vec3f::dot(scene.getViewDir() , scene.getUpDir() );
	if( fabs(dot-1.f) < 0.001 ){
		std::cout << "Error: The viewing direction and up direction are too close to being parallel.\n";
		exit(0);
	}
	
	
	scene.verifySetup();
	
	return scene;
	
}



bool Parser::parseWord(int& v, int& vt, int& vn, std::string& lineformat, std::stringstream& wordstream){
	
	int val1=0, val2=0, val3=0;
	char c1 = '\0';
	char c2 = '\0';
	
	wordstream >> val1 >> c1 >> val2 >> c2 >> val3;
	
	// v line format		
	if( val1 > 0 && c1 == '\0' && val2 == 0 && c2 == '\0' && val3 == 0 && (lineformat == "unknown" || lineformat == "v") ){
		lineformat = "v";
		v = val1;
		vt = 0;
		vn = 0;
		return true;
	}
	
	// v vn line format
	else if( val1 > 0 && c1 == '~' && val2 > 0 && c2 == '\0' && val3 == 0 && (lineformat == "unknown" || lineformat == "v_vn") ){
		lineformat = "v_vn";
		v = val1;
		vt = 0;
		vn = val2;
		return true;
	}
	
	// v vt line format
	else if( val1 > 0 && c1 == '/' && val2 > 0 && c2 == '\0' && val3 == 0 && (lineformat == "unknown" || lineformat == "v_vt") ){
		lineformat = "v_vt";
		v = val1;
		vt = val2;
		vn = 0;
		return true;
	}
	
	// v vt vn line format
	else if( val1 > 0 && c1 == '/' && val2 > 0 && c2 == '/' && val3 > 0 && (lineformat == "unknown" || lineformat == "v_vt_vn" ) ){
		lineformat = "v_vt_vn";
		v = val1;
		vt = val2;
		vn = val3;
		return true;
	}
	
	else {
		std::cout << "Error: Invalid data was found on a line starting with 'f' which is supposed to specify 3 faces.\n";
		exit(0);
	}
	
}


// found this function here:   http://stackoverflow.com/questions/5878775/how-to-find-and-replace-string
std::string Parser::replaceString(std::string subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}


void Parser::parseFace(Vec3i& v1, Vec3i& v2, Vec3i& v3, std::stringstream& linestream){

	std::vector< std::tuple<int,int,int> > faceData;

	std::string word;
	std::string lineformat = "unknown";
	while( linestream >> word ){
		
		word = replaceString(word,"//"," ~ ");
		word = replaceString(word,"/"," / ");
		
		std::stringstream wordstream(word);
		
		int vVal, vtVal, vnVal;

		if( parseWord(vVal,vtVal,vnVal,lineformat,wordstream) ){
			faceData.push_back( std::make_tuple(vVal,vtVal,vnVal) );
		}
	}
	
	if( faceData.size() != 3 ){
		std::cout << "Error: Face data line did not contain exactly 3 valid vertex data words.\n";
		exit(0);
	} else {
		
		v1.x = std::get<0>( faceData[0] );
		v1.y = std::get<1>( faceData[0] );
		v1.z = std::get<2>( faceData[0] );
		
		v2.x = std::get<0>( faceData[1] );
		v2.y = std::get<1>( faceData[1] );
		v2.z = std::get<2>( faceData[1] );
		
		v3.x = std::get<0>( faceData[2] );
		v3.y = std::get<1>( faceData[2] );
		v3.z = std::get<2>( faceData[2] );
		
	}
	// todo: set v, vt, and vn properly
	
}




// Parses a collection of 3 floats and returns them as a 3d float vector
Vec3f Parser::parseVec3f(std::string var, std::stringstream& ss){
	float x = -9999999, y=-9999999, z=-9999999;
	std::string extra = "";
	ss >> x >> y >> z >> extra;

	if( x == -9999999 || y == -9999999 || z == -9999999 ){
		std::cout << "Error: 3d float vector data was not properly supplied for field:  " << var << std::endl;
		std::cout << "--- Please supply three floats, each separated by a space. E.g., " << var  << " " << 0.5 << " " << 0.5 << " " << 1.0 << std::endl;
		exit(0);
	}

	if( extra != "" ){
		extraneousError(var);
	}
	
	return Vec3f(x,y,z);
}

// Parses a collection of 2 floats and returns them as a 2d float vector
Vec2f Parser::parseVec2f(std::string var, std::stringstream& ss){
	float x = -9999999, y=-9999999;
	std::string extra = "";
	ss >> x >> y >> extra;

	if( x == -9999999 || y == -9999999 ){
		std::cout << "Error: 2d float vector data was not properly supplied for field:  " << var << std::endl;
		std::cout << "--- Please supply two floats, each separated by a space. E.g., " << var  << " " << 0.5 << " " << 0.5 << std::endl;
		exit(0);
	}

	if( extra != "" ){
		extraneousError(var);
	}
	
	return Vec2f(x,y);
}



// Parses a float
float Parser::parseFloat(std::string var, std::stringstream& ss){
	float f = -9999999;
	std::string extra = "";
	ss >> f >> extra;
	
	if( f == -9999999 ){
		std::cout << "Error: float data was not properly supplied for field:  " << var << std::endl;
		std::cout << "--- Please supply a float after the var name. E.g., " << var  << " " << 1.0 << std::endl;
		exit(0);
	}
	
	if( extra != "" ){
		extraneousError(var);
	}
	
	return f;
}

// Parses a collection of 2 ints and returns them as a 2d integer vector
Vec2i Parser::parseVec2i(std::string var, std::stringstream& ss){
	int x = -9999999, y = -9999999;
	std::string extra;
	ss >> x >> y >> extra;
	
	if( x == -9999999 || y == -9999999 ){
		std::cout << "Error: 2d int vector data was not properly supplied for field:  " << var << std::endl;
		std::cout << "--- Please supply two ints, each separated by a space. E.g., " << var  << " " << 1 << " " << 3 << std::endl;
		exit(0);
	}
	
	if( extra != "" ){
		extraneousError(var);
	}
	
	return Vec2i(x,y);
}



void Parser::extraneousError(std::string var){
	std::cout << "Error: Extraneous information was included after the 3d vector data for field:  " << var << std::endl;
	exit(0);	
}

// Removes the suffix from a filename (e.g., removes .txt from the end of a filename)
std::string Parser::removeSuffix(const std::string& filename){
	
	int suffixDelimIdx = filename.rfind('.');
	std::string outname = filename;
	outname.erase( outname.begin() + suffixDelimIdx, outname.end() );
	return outname;
	
}


