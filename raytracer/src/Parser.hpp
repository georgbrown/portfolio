/**
 * \author George Brown
 *
 * \file Parser.hpp 
 * \brief The scene information for all objects, materials, and textures is stored in text files.
 *        A custom parser is used to extract the information and build the entities in the program.
 */

#ifndef PARSER_HPP
#define PARSER_HPP

#include "Math.hpp"
#include "Object.hpp"
#include "Sphere.hpp"
#include "Scene.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include <fstream>
#include <sstream>
#include <utility>
#include <cstdlib>
#include <tuple>

/*! \class Parser Parser reads the input file, parses it, and produces the scene */
class Parser {
	
	public:
	
		/*! Parser constructor */
		Parser();
		
		
		/*! Parses command-line arguments 
		 * \param argc The number of arguments
		 * \param argv The arguments
		 * \return The complete parsed scene with all entities created and initialized */
		static Scene parse(int argc, char** argv);
		
		
		/*! Helper function for finding and replacing a string
		 * \param subject The content to search
		 * \param search The term to search for
		 * \param replace The term to replace with
		 * \return The subject string */
		static std::string replaceString(std::string subject, const std::string& search, const std::string& replace);
		
		
		/*! Parses a tuple of vertex, texture, and normal data
		 * \param v The vertex index
		 * \param vt The texture index
		 * \param vn The normal index
		 * \param lineformat The style format for encoding vertex, texture, normal data
		 * \param wordstream The text data to extract information from
		 * \return Success boolean flag */
		static bool parseWord(int& v, int& vt, int& vn, std::string& lineformat, std::stringstream& wordstream);
		
		
		/*! Parses data for an entire face (three vertices) including vert, texture, and normal data.
		 * \param v The vertex index
		 * \param vt The texture index
		 * \param vn The normal index
		 * \param ss The text data to extract information from */
		static void parseFace(Vec3i& v, Vec3i& vt, Vec3i& vn, std::stringstream& ss);
		
		
		/*! Parses a 2D float vector from a stringstream object
		 * \param var Label for the item whose associated data is to be parsed
		 * \param ss Text to parse from
		 * \return The parsed Vec2f */
		static Vec2f parseVec2f(std::string var, std::stringstream& ss);
		
		
		/*! Parses a 3D float vector from a stringstream object
		 * \param var Label for the item whose associated data is to be parsed
		 * \param ss Text to parse from
		 * \return The parsed Vec3f */
		static Vec3f parseVec3f(std::string var, std::stringstream& ss);
		
		
		/*! Parses a float from a stringstream object
		 * \param var Label for the item whose associated data is to be parsed
		 * \param ss Text to parse from
		 * \return The parsed float */
	    static float parseFloat(std::string var, std::stringstream& ss);
	    
	    
	    /*! Parses a 2D int vector from a stringstream object
	     * \param var Label for the item whose associated data is to be parsed
	     * \param ss Text to parse from
	     * \return The parsed Vec2i */
		static Vec2i parseVec2i(std::string var, std::stringstream& ss);
		
		
		/*! Standard print message called for field "var", which tells the user
		 * that extraneous data was found on an input line
		 * \param var Label for the item with extraneous data */
		static void extraneousError(std::string var);
		
		
		/*! Removes the suffix from a given filename string
		 * \param filename The filename string whose suffix is to be removed
		 * \return Filename without the suffix */
		static std::string removeSuffix(const std::string& filename);
	

};

#endif
