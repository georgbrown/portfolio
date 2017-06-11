/**
 * \author George Brown
 *
 * \file Material.hpp 
 * \brief Each object can have its own unique material properties. The Blinn-Phong
 *        model is used, which requires specification of the ambient, diffuse, and
 *        specular coefficients for each object, as well as the ambient and specular
 *        intrinsic colors, and the rate of specular falloff.
 */

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Math.hpp"

/*! \class Material This class stores data which describes intrinsic color properties of an object
 There is an ambient color which is present even in the absence of lights
 The diffuse and specular terms produce different color effects depending on the
 characteristics of the lights in the scene */
class Material {
	
	public:
	
		/*! Material constructor */
		Material();
		
		/*! Getter for Od
		 *  \return The intrinsic color of the object as a 3D RGB vector */
		Vec3f getOd() const;
		
		/*! Getter for Os
		 * \return The color of the specular highlight as an RGB tuple */
		Vec3f getOs() const;
		
		/*! Getter for ka
		 *  \return The ambient coefficient */
		float getKa() const;
		
		/*! Getter for kd
		 *  \return The diffuse coefficient */
		float getKd() const;
		
		/*! Getter for ks
		 * \return The specular coefficient */
		float getKs() const;
		
		/*! Getter for n
		 * \return The coefficient for the specular falloff */
		float getN() const;
		
		/*! Sets the intrinsic color of the object
		 *  \param Od_ The color of the object as an RGB tuple */
		void setOd( Vec3f Od_ );
		
		/*! Sets the color of the specular highlight
		 *  \param Os_ The color of the specular highlight */
		void setOs( Vec3f Os_ );
		
		/*! Sets the ambient coefficient
		 * \param ka_ The ambient coefficient (between 0-1) */
		void setKa( float ka_ );
		
		/*! Sets the diffuse coefficient
		 * \param kd_ The diffuse coefficient (between 0-1) */
		void setKd( float kd_ );
		
		/*! Sets the specular coefficient
		 * \param ks_ The specular coefficient (between 0-1) */
		void setKs( float ks_ );
		
		/*! Sets the coefficient for the specular falloff
		 * \param n_ The coefficient for the specular falloff */
		void setN( float n_ );
	
	private:
	
		/*! Intrinsic color of the object */
		Vec3f Od;
		
		/*! Color of the specular highlight */
		Vec3f Os;
		
		/*! Ambient cofficient */
		float ka;
		
		/*! Diffuse coefficient */
		float kd;
		
		/*! Specular coefficient */
		float ks;
		
		/*! Coefficient for the specular falloff */
		float n;
	
};

#endif
