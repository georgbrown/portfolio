/**
 * \author George Brown
 *
 * \file Triangle.hpp 
 * \brief The fundamental element which is used as building blocks for all more complex objects in
 *        the scene. Triangles consist of three vertices, and may have material and texture data.
 */

#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Object.hpp"
#include "Vert.hpp"
#include "Ray.hpp"
#include "Texture.hpp"

/*! \class Triangle Triangle Class, consists of three vertices, Blinn-Phong material information, and optional texture info */
class Triangle : public Object {
	
	public:
	
		/*! Triangle constructor
		 * \param vert0_ The first vertex of the triangle
		 * \param vert1_ The second vertex of the triangle
		 * \param vert2_ The third vertex of the triangle
		 * \param material_ Material information for the triangle
		 * \param texture_ Optional texture to apply to the triangle */
		Triangle(Vert* vert0_, Vert* vert1_, Vert* vert2_, Material* material_, Texture* texture_ = 0);
	
		/*! Determines whether a ray intersects the triangle. 
		 * \param ray The ray shot out by the raytracer
		 * \param rayPayload The associated payload data for the ray
		 * \return True if the ray intersects the triangle, false otherwise */
		bool intersect(Ray& ray, RayPayload& rayPayload);
		
		/*! Determines the barycentric coordinates in the triangle for a given point 
		 * \param point A point in 3D space
		 * \return The barycentric coordinates as a 3D float vec */
		Vec3f getBarycentricCoords(Vec3f point);
		
		/*! Determines unit normal of the triangle.
		 * \param pointOnSurface The point on the surface of the triangle
		 * \return Unit surface normal of the triangle */
		Vec3f getUnitSurfaceNormal(Vec3f pointOnSurface);
		
		/*! Helper function for determining whether a point is inside of the triangle
		 * \param point A point in 3D space
		 * \return True if the point is inside the triangle, false otherwise */
		bool isInside(Vec3f point);
	
		/*! Sets the conditional flag for the vertex normals being provided
		 * \param normalsProvided_ Conditional flag status to set */
		void setNormalsProvided(bool normalsProvided_);
	
	private:
	
		/*! Triangle normal */
		Vec3f normal;
		
		/*! The vertices of the triangle */
		Vert* verts[3];
		
		/*! Precomputed values used for ray-triangle interactions */
		float A, B, C, D;
		
		/*! Conditional flag which is true if the vertex normals are provided */
		bool normalsProvided;
	
	
};

#endif
