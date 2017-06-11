/**
 * \author George Brown
 *
 * \file Vert.hpp 
 * \brief A vert is a point in space which may be component of one or more triangles
 *        in the scene. Vertices are specified each on their own line in a config file.
 */

#ifndef VERT_HPP
#define VERT_HPP

#include "Math.hpp"

/*! \class Vert A point in space which may be a building block for triangles. Has a position,
 *         normal, and possible texture coordinates. */
class Vert {
	
	public:
	
		/*! Vert constructor
		 * \param pos_ Position of the vertex */
		Vert(Vec3f pos_);
	
		/*! Getter for vert pos
		 * \return Position of the vertex */
		Vec3f getPos() const;
		
		/*! Getter for vert normal
		 * \return Normal of the vertex */
		Vec3f getNormal() const;
		
		/*! Getter for vert texture coords
		 * \return Texture coordiantes of the vertex */
		Vec2f getTextureCoords() const;
	
		/*! Setter for vertex texture coordinates
		 * \param coords_ The texture coordinates to set for the vertex */
		void setTextureCoords(Vec2f coords_);
		
		/*! Setter for the vertex normal
		 * \param normal_ Normal to set for the vertex */
		void setNormal(Vec3f normal_);
	
	private:
	
		/*! Vertex position */
		Vec3f pos;
		
		/*! Vertex normal */
		Vec3f normal;
		
		/*! Vertex texture coordinates */
		Vec2f textureCoords;
	
};

#endif
