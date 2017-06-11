/**
 * \author George Brown
 *
 * \file RayPayload.hpp 
 * \brief When a ray hits an object, that object's particular characteristics
 *        become relevant for deciding how the corresponding pixel will be colored.
 *        This data is stored in the RayPayload and is used by the other subsystems.
 */

#ifndef RAY_PAYLOAD_HPP
#define RAY_PAYLOAD_HPP

#include "Object.hpp"
#include "Material.hpp"
#include "Texture.hpp"

class Object; // forward declaration

/*! \class RayPayload Class which contains relevant data about objects which a ray hits */
class RayPayload {
	
	public:
	
		/*! RayPayload constructor */
		RayPayload();
		
		
		/*! Getter for the object pointer
		 * \return Pointer to the RayPayload's object */
		Object* getObject();
		
		
		/*! Getter for the material pointer
		 * \return Pointer to the RayPayload's material */
		Material* getMaterial();
		
		
		/*! Getter for the texture pointer
		 * \return Pointer to the RayPayload's texture */
		Texture* getTexture();
		
		
		/*! Getter for the texture color
		 * \return The texture color as an RGB */
		Vec3f getTextureColor() const;
		
		
		/*! Get the distance the ray travelled before intersecting the object
		 * \return Distance the ray travelled */
		float getDistance() const;
		
		
		/*! Set the RayPayload object pointer
		 * \param object_ Pointer to the object */
		void setObject(Object* object_);
		
		
		/*! Set the RayPayload material pointer
		 * \param material_ Pointer to the material */
		void setMaterial(Material* material_);
		
		
		/*! Set the RayPayload texture pointer
		 * \param texture_ Pointer to the texture */
		void setTexture(Texture* texture_);
		
		
		/*! Set the RayPayload texture color
		 * \param textureColor_ The color of the texture */
		void setTextureColor(Vec3f textureColor_);
		
		
		/*! Set the distance the ray travelled before intersecting
		 * \param distance_ Distance the tray travelled before intersecting */
		void setDistance(float distance_);
	
	private:
	
		/*! Pointer to the object hit by the ray */
		Object* object;
		
		/*! Pointer to the material of the object hit by the ray */
		Material* material;
		
		/*! Pointer to the texture of the object hit by the ray */
		Texture* texture;
		
		/*! The texture color of the object hit by the ray, in RGB */
		Vec3f textureColor;
		
		/*! The distance the ray travelled from the origin */
		float distance;
	
};


#endif
