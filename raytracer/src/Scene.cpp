#include "Scene.hpp"
#include <iostream>

Scene::Scene(){
	
	eyeSet = false;
	viewSet = false;
	upSet = false;
	fovvSet = false;
	envDimsSet = false;
	bkgColorSet = false;
	
}

// Getters //
Vec3f Scene::getEyePos() const{
	return eyePos;
}

Vec3f Scene::getViewDir() const{
	return viewDir;
}

Vec3f Scene::getUpDir() const{
	return upDir;
}

float Scene::getFovv() const{
	return fovv;
}

Vec2i Scene::getEnvDims() const{
	return envDims;
}

Vec3f Scene::getBkgColor() const{
	return bkgColor;
}

std::vector<Object*> Scene::getObjects() const{
	return objects;	
}
		
		
std::string Scene::getSceneName() const{
	return sceneName;
}
		
// Setters //
void Scene::setEyePos(Vec3f eyePos_){
	eyePos = eyePos_;
	eyeSet = true;
}

void Scene::setViewDir(Vec3f viewDir_){
	viewDir = Vec3f::normalize(viewDir_);
	viewSet = true;
}

void Scene::setUpDir(Vec3f upDir_){
	upDir = Vec3f::normalize(upDir_);
	upSet = true;
}

void Scene::setFovv(float fovv_){
	fovv = fovv_;
	fovvSet = true;
}

void Scene::setEnvDims(Vec2i envDims_){
	envDims = envDims_;
	envDimsSet = true;
}

void Scene::setBkgColor(Vec3f bkgColor_){
	bkgColor = bkgColor_;
	bkgColorSet = true;
}

void Scene::setSceneName(std::string sceneName_){
	sceneName = sceneName_;
}


// Data printing for debugging purposes //
void Scene::printData() const{
	
	std::cout << "Scene data: \n";
	std::cout << "Eye pos: " << eyePos.to_str() << std::endl;
	std::cout << "View dir: " << viewDir.to_str() << std::endl;
	std::cout << "Up dir: " << upDir.to_str() << std::endl;
	std::cout << "Fovv: " << fovv << std::endl;
	std::cout << "Env dims: " <<  envDims.to_str() << std::endl;
	std::cout << "Bkg color: " << bkgColor.to_str() << std::endl;
	
	//std::cout << "num point lights .. " << pointLights.size() << std::endl;
	//std::cout << "num dir lights .. " << directionalLights.size() << std::endl;
	
	
	// computing vertex normals here...
	/*std::cout << "computing vertex normals .. \n";
	for(int i = 0; i < verts.size(); i++){
	
		Vec3f vecSum(0.f,0.f,0.f);
	
		for(int j = 0; j < objects.size(); j++){
		
			Triangle* tri = dynamic_cast<Triangle*>( objects[j] );
			
			if( tri->verts[0] == verts[i] || tri->verts[1] == verts[i] || tri->verts[2] == verts[i] ){
				vecSum = vecSum + tri->normal;
			}
		
		}
		
		Vec3f avgNormal = Vec3f::normalize( vecSum );
		
		std::cout << avgNormal.to_str() << std::endl;
		
	} */
	
	
	
	
}


// Method which adds new objects to the collection of objects in the scene //
void Scene::addObject(Object* obj){
	objects.push_back( obj );
}

void Scene::verifySetup(){
	
	if( !eyeSet ){
		std::cout << "Error: eye was not set in the input file.\n";
		exit(0);
	} else if( !viewSet ){
		std::cout << "Error: viewdir was not set in the input file. \n";
		exit(0);
	} else if( !upSet ){
		std::cout << "Error: updir was not set in the input file. \n";
		exit(0);
	} else if( !fovvSet ){
		std::cout << "Error: fovv was not set in the input file. \n";
		exit(0);
	} else if( !envDimsSet ){
		std::cout << "Error: imsize was not set in the input file. \n";
		exit(0);
	} else if( !bkgColorSet ){
		std::cout << "Error: bkgcolor was not set in the input file. \n";
		exit(0);
	}
	
}


// Adds a point light to the scene
void Scene::addPointLight(PointLight* pointLight){
	lights.push_back( pointLight );
}

// Adds a directional light to the scene
void Scene::addDirectionalLight(DirectionalLight* directionalLight){
	lights.push_back( directionalLight );
}


void Scene::addVert(Vec3f pos_){
	
	Vert* vert = new Vert(pos_);
	verts.push_back(vert);
	
}

void Scene::addTextureCoords(Vec2f coords_){
	
	if( coords_.x < 0.f || coords_.x > 1.f || coords_.y < 0.f || coords_.y > 1.f ){
		std::cout << "Error: texture coords data specified in a vt row in config file is invalid. The x and y values must be between 0-1.\n";
		exit(0);
	}
	
	textureCoords.push_back( coords_ );
}

void Scene::addNormal(Vec3f normal_){
	
	if( fabs( Vec3f::norm(normal_) - 1.f ) > 0.001 ){
		std::cout << "Error: normals data specified in a vn row in config file is invalid. Its norm is not 1.\n";
		exit(0);
	}
	
	normals.push_back( Vec3f::normalize(normal_) );
}

void Scene::addTriangle(Vec3i v1_, Vec3i& v2_, Vec3i& v3_, Material* material_, Texture* texture_ ){
	
	if( v1_.x > 0 && v1_.x <= verts.size() &&
	    v2_.x > 0 && v2_.x <= verts.size() && 
	    v3_.x > 0 && v3_.x <= verts.size() ){
	
		Vert* v1 = verts[v1_.x-1];
		Vert* v2 = verts[v2_.x-1];
		Vert* v3 = verts[v3_.x-1];
		
		Triangle* tri = new Triangle(v1,v2,v3,material_,0);
	
		if( v1_.y > 0 && v1_.y <= textureCoords.size() && 
		    v2_.y > 0 && v2_.y <= textureCoords.size() &&
		    v3_.y > 0 && v3_.y <= textureCoords.size() ){
		
			v1 -> setTextureCoords( textureCoords[v1_.y-1] );
			v2 -> setTextureCoords( textureCoords[v2_.y-1] );
			v3 -> setTextureCoords( textureCoords[v3_.y-1] );
			tri -> setTexture( texture_ );
		
		}
		
		else if( v1_.y != 0 || v2_.y != 0 || v3_.y != 0 ){
			std::cout << "Error: vt1, vt2, vt3 data identified, but does not correspond to registered"
			          << " texture coordinates in the system. \n";
			exit(0);		
		}
		
		if( v1_.z > 0 && v1_.z <= normals.size() &&
			v2_.z > 0 && v2_.z <= normals.size() &&
			v3_.z > 0 && v3_.z <= normals.size() ){
				
			v1 -> setNormal( normals[v1_.z-1] );
			v2 -> setNormal( normals[v2_.z-1] );
			v3 -> setNormal( normals[v3_.z-1] ); 
			tri -> setNormalsProvided(true);
		
		}
		
		else if( v1_.z != 0 || v2_.z != 0 || v3_.z != 0 ){
			std::cout << "Error: vn1, vn2, vn3 data identified, but does not correspond to registered"
					  << " normals data in the system. \n";
			exit(0);
		}
		
		objects.push_back( tri );
		
		
	} else {
		
		std::cout << "Error: v1, v2, v3 data is not all valid. Each must be an integer corresponding"
		          << " to a registered vertex in the system. \n";
		exit(0);
	}
	
}


void Scene::traceRay(Ray& ray, RayPayload& rayPayload){
	
	for(int i = 0; i < objects.size(); i++){	
		if( objects[i]->intersect( ray , rayPayload ) ){
			rayPayload.setObject(objects[i]);
		}
	}
	
}

Vec3f Scene::shadeRay(Ray& ray, RayPayload& rayPayload){
	
	// Extracting material data	
	Material* mat = rayPayload.getMaterial();
	
	// Extracting the object data
	Object* obj = rayPayload.getObject();
	
	// Point of intersection with the object
	Vec3f intersectPoint = ray.getOrigin() + rayPayload.getDistance() * ray.getDir();
	
	// Vector parameters for computing Phong illumination
	Vec3f N = obj -> getUnitSurfaceNormal( intersectPoint );
	Vec3f V = Vec3f::normalize( eyePos - intersectPoint );
	
	Vec3f diffuseColor;
	if( rayPayload.getTexture() != 0 && rayPayload.getTexture() != NULL ){
		diffuseColor = rayPayload.getTextureColor();
	} else {
		diffuseColor = mat->getOd();
	}
	
	// The color data, initialized to the ambient color in the absence of lights.
	Vec3f Ilam = mat->getKa() * diffuseColor;
	
	// Looping through all lights in the scene and adding the diffuse and specular components
	for(int i = 0; i < lights.size(); i++){
			
		// Phong illumination vectors
		Vec3f L = lights[i] -> computeL(intersectPoint);
		Vec3f H = Vec3f::normalize( L + V );
			
		// Boolean which is set to true if the light in question is blocked by another object
		bool blocked = lights[i] -> isBlocked( objects, obj, intersectPoint );	
		
		// If the object is not blocked, we add the specular and diffuse contributions of the light
		if( !blocked ){
				
			Vec3f diffuseTerm = mat->getKd() * diffuseColor * std::max( ( Vec3f::dot(N,L) ) , 0.f );
			Vec3f specularTerm = mat->getKs() * mat->getOs() * powf( std::max( ( Vec3f::dot(N,H) ) , 0.f), mat->getN() );
			Vec3f rgb = lights[i]->getRGB();
				
			float lightIntensityR = rgb.x * (diffuseTerm.x + specularTerm.x);
			float lightIntensityG = rgb.y * (diffuseTerm.y + specularTerm.y);
			float lightIntensityB = rgb.z * (diffuseTerm.z + specularTerm.z);

			Ilam = Ilam + Vec3f( lightIntensityR , lightIntensityG, lightIntensityB );

		}
			
	}
	
	// The RGB values are clamped to the range 0-1 to avoid overflow
	return Vec3f::clamp(Ilam,0,1);

	
}















