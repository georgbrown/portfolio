#include "Object.hpp"

Object::Object(Material* material_, Texture* texture_){
	material = material_;
	texture = texture_;
}

Material* Object::getMaterial(){
	return material;
}
		
Texture* Object::getTexture(){
	return texture;
}

void Object::setMaterial(Material* material_){
	material = material_;
}

void Object::setTexture(Texture* texture_){
	texture = texture_;
}
