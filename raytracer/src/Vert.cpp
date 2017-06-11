#include "Vert.hpp"
#include <iostream>

Vert::Vert(Vec3f pos_)
	: pos(pos_){
}

Vec3f Vert::getPos() const{
	return pos;
}
		
Vec3f Vert::getNormal() const{
	return normal;
}
		
Vec2f Vert::getTextureCoords() const{
	return textureCoords;
}

void Vert::setTextureCoords(Vec2f coords_){
	textureCoords = coords_;
}

void Vert::setNormal(Vec3f normal_){
	normal = normal_;
}
