/**
 * \author George Brown
 *
 * \file Object.hpp 
 * \brief A base template for all objects which may be placed in the environment.
 *        Objects have material parameters and can also be texture.
 */

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Math.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "Ray.hpp"
#include "RayPayload.hpp"

class RayPayload; // forward declaration

/*! \class Object Base class from which all objects (spheres, and other shapes) may be defined */
class Object {
	
	public:
	
		/*! Object constructor 
		 * \param material_ The material information for the object
		 * \param texture_ The texture to apply to the object (optional) */
		Object(Material* material_, Texture* texture_ = 0);
	
	
		/*! Determines whether a ray intersects the object. If so, returns a scalar t such that
		 * ray.origin + t * ray.dir is the position on the object where the intersection occurs
		 * Else, returns -1.  This virtual method must be defined by an inheriting class.
		 * \param ray The ray which the intersection check is performed with
		 * \param rayPayload Metadata associated with the ray, used by the raytracer system
		 * \return Boolean true if intersecting, else false. */
		virtual bool intersect(Ray& ray, RayPayload& rayPayload) = 0;
		
		/*! Determines unit normal at a particular point on the surface of an object.
		 * \param pointOnSurface The point on the surface of the object in which to compute the normal.
		 * \return Unit surface normal at point on surface */
		virtual Vec3f getUnitSurfaceNormal(Vec3f pointOnSurface) = 0;
		
		/*! Getter for object's material
		 * \return Pointer to the object's material */
		Material* getMaterial();
		
		/*! Getter for object's texture
		 * \return Pointer to the object's texture */
		Texture* getTexture();
		
		/*! Sets the object's material
		 * \param material_ Pointer to the material to assign to the object */
		void setMaterial(Material* material_);
		
		/*! Sets the object's texture
		 * \param texture_ Pointer to the texture to assign to the object */
		void setTexture(Texture* texture_);
		
	protected:
	
		/*! Material data for Blinn-Phong */
		Material* material;
		
		/*! Texture to apply */
		Texture* texture;
	
};

#endif
