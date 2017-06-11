#include "RayPayload.hpp"

RayPayload::RayPayload(){
	
	object = 0;
	material = 0;
	distance = 100000000;
	textureColor = Vec3f(-1.f,-1.f,-1.f);
	
}


Object* RayPayload::getObject(){
	return object;
}
		
Material* RayPayload::getMaterial(){
	return material;
}
		
Texture* RayPayload::getTexture(){
	return texture;
}
		
Vec3f RayPayload::getTextureColor() const{
	return textureColor;
}
		
float RayPayload::getDistance() const{
	return distance;
}
		
void RayPayload::setObject(Object* object_){
	object = object_;
}
		
void RayPayload::setMaterial(Material* material_){
	material = material_;
}
		
void RayPayload::setTexture(Texture* texture_){
	texture = texture_;
}
		
void RayPayload::setTextureColor(Vec3f textureColor_){
	textureColor = textureColor_;
}
		
void RayPayload::setDistance(float distance_){
	distance = distance_;
}
