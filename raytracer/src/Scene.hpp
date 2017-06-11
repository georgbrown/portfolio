/**
 * \author George Brown
 *
 * \file Scene.hpp 
 * \brief The scene is the environment where all entities reside. Objects are placed
 *        in the scene as described in the configuration files, and lights are scattered
 *        across the scene too to illuminate the objects.  
 */

#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <utility>
#include <cstdlib>
#include "Object.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "Math.hpp"
#include "Vert.hpp"
#include "RayPayload.hpp"
#include "Triangle.hpp"

/*! \class Scene Class which stores all the scene data parsed from input
 * Data is stored using custom vector classes and physical objects
 * are stored in a vector */
class Scene {
	
	public:
	
		/*! Scene constructor */
		Scene();
		
		/*! Getter for eye pos
		 * \return The eye position */
		Vec3f getEyePos() const;
		
		/*! Getter for view dir
		 * \return The viewing direction */
		Vec3f getViewDir() const;
		
		/*! Getter for up dir
		 * \return The up direction */
		Vec3f getUpDir() const;
		
		/*! Getter for fovv
		 * \return The vertical field of view */
		float getFovv() const;
	
		/*! Getter for env dims
		 * \return The environment width and height as a Vec2i */
		Vec2i getEnvDims() const;
		
		/*! Getter for bkg color
		 * \return The background color as an RGB tuple */
		Vec3f getBkgColor() const;
		
		/*! Getter for the objects
		 * \return Vector of pointers to all objects in the scene */
		std::vector<Object*> getObjects() const;
		
		/*! Getter for the scene name
		 * \return String identifier for the scene name */
		std::string getSceneName() const;
		
		/*! Sets the eye position
		 * \param eyePos_ Eye position */
		void setEyePos(Vec3f eyePos_);
		
		/*! Sets the view dir
		 * \param viewDir_ Viewing direction */
		void setViewDir(Vec3f viewDir_);
		
		/*! Sets the up dir
		 * \param upDir_ Up direction */
		void setUpDir(Vec3f upDir_);
		
		/*! Sets the fovv
		 * \param fovv_ Vertical field of view */
		void setFovv(float fovv_);
		
		/*! Sets the env dims
		 * \param envDims_ The environment width and height as a Vec2i */
		void setEnvDims(Vec2i envDims_);
		
		/*! Sets the bkg color
		 * \param bkgColor_ The background color as an RGB tuple */
		void setBkgColor(Vec3f bkgColor_);
		
		/*! Sets the scene name
		 * \param sceneName The scene name as a string identifier */
		void setSceneName(std::string sceneName);
		
		/*! Prints data for debugger purposes */
		void printData() const;
		
		/*! Adds an object to the scene
		 * \param obj The object to add to the scene */
		void addObject(Object* obj);
		
		/*! Adds a point light to the scene
		 * \param pointLight The point light to add to the scene */
		void addPointLight(PointLight* pointLight);
		
		/*! Adds a directional light to the scene
		 * \param directionalLight The directional light to add to the scene */
		void addDirectionalLight(DirectionalLight* directionalLight);
		
		/*! Adds a vertex to the scene
		 * \param pos_ The position in which to add a vertex to the scene */
		void addVert(Vec3f pos_);
		
		/*! Adds texture coordinate data to the scene
		 * \param coords_ The texture coordinate data to add to the scene */
		void addTextureCoords(Vec2f coords_);
		
		/*! Adds normal data to the scene
		 * \param normal_ The normal data to add to the scene */
		void addNormal(Vec3f normal_);
		
		/*! Adds a triangle to the scene
		 * \param v1_ The first vertex of the triangle
		 * \param v2_ The second vertex of the triangle
		 * \param v3_ The third vertex of the triangle
		 * \param material_ The material of the triangle
		 * \param texture_ The texture of the triangle */
		void addTriangle(Vec3i v1_, Vec3i& v2_, Vec3i& v3_, Material* material_, Texture* texture_);
		
		/*! Verifies that everything is setup correctly in the scene */
		void verifySetup();
		
		/*! Traces a ray through the scene
		 * \param ray The ray to shoot through the scene
		 * \param rayPayload The associated payload data for the ray */
		void traceRay(Ray& ray, RayPayload& rayPayload);
		
		/*! Apply phong illumination and shadows
		 * \param ray The ray to shoot through the scene
		 * \param rayPayload The associated payload data for the ray
		 * \return RGB color result */
		Vec3f shadeRay(Ray& ray, RayPayload& rayPayload);
		
		// Flags which keep track of what has and has not been set
		
	private:
		
		/*! The "origin" where rays emanate from */
		Vec3f eyePos;
		
		/*! Viewing direction */
		Vec3f viewDir;
		
		/*! The up direction */
		Vec3f upDir;
		
		/*! Vertical field of view */
		float fovv;
		
		/*! Width and height of the scene, in pixels (e.g. 800x600) */
		Vec2i envDims; 
		
		/*! Background color */
		Vec3f bkgColor;
		
		/*! Collection of all objects in the scene */
		std::vector<Object*> objects; 
		
		/*! Collection of all lights in the scene */
		std::vector<Light*> lights;
		
		/*! Collection of all vertices in the scene */
		std::vector<Vert*> verts;
		
		/*! Collection of all normals in the scene */
		std::vector<Vec2f> textureCoords;
		
		/*! Collection of all normals in the scene */
		std::vector<Vec3f> normals;
		
		/*! Name of the scene */
		std::string sceneName;
		
		/*! Flag to keep track of whether the eye has been set */
		bool eyeSet;
		
		/*! Flag to keep track of whether the view dir has been set */
		bool viewSet;
		
		/*! Flag to keep track of whether the up dir has been set */
		bool upSet;
		
		/*! Flag to keep track of whether the vertical fov has been set */
		bool fovvSet;
		
		/*! Flag to keep track of whether the env dims have been set */
		bool envDimsSet;
		
		/*! Flag to keep track of whether the background color has been set */
		bool bkgColorSet;
	
};

#endif

