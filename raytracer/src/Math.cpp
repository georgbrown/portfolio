#include "Math.hpp"


// Method which converts 2d int vector data to output stream data
std::string Vec2i::to_str() const{
	std::stringstream ss;
	ss << x << ' ' << y;
	return ss.str();
}

// Method which converts 3d int vector data to output stream data
std::string Vec3i::to_str() const{
	std::stringstream ss;
	ss << x << ' ' << y << ' ' << z;
	return ss.str();
}


// Method which converts 2d float vector data to output stream data
std::string Vec2f::to_str() const{
	std::stringstream ss;
	ss << x << ' ' << y;
	return ss.str();
}

// Method which converts 3d float vector data to output stream data
std::string Vec3f::to_str() const {
	std::stringstream ss;
	ss << x << ' ' << y << ' ' << z;
	return ss.str();
}


// Method which computes the cross product of two input vectors
Vec3f Vec3f::cross(Vec3f v1, Vec3f v2){
	Vec3f v3;
	v3.x = v1.y*v2.z - v1.z*v2.y;
	v3.y = v1.z*v2.x - v1.x*v2.z;
	v3.z = v1.x*v2.y - v1.y*v2.x;
	return v3;
}

// Method which computes the dot product of two input vectors
float Vec3f::dot(Vec3f v1, Vec3f v2){
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}


// Method which returns the normalized result of an input vector
Vec3f Vec3f::normalize(Vec3f vec){

	Vec3f res;
	float mag = sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
	res.x = vec.x / mag;
	res.y = vec.y / mag;
	res.z = vec.z / mag;
	return res;
	
}

float Vec3f::norm(Vec3f vec){	
	return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}

Vec3f Vec3f::clamp(Vec3f vec, float valMin, float valMax){
	
	Vec3f res = vec;
	if( res.x < valMin )  res.x = valMin;
	if( res.x > valMax )  res.x = valMax;
	if( res.y < valMin )  res.y = valMin;
	if( res.y > valMax )  res.y = valMax;
	if( res.z < valMin )  res.z = valMin;
	if( res.z > valMax )  res.z = valMax;
	
	return res;
	
}


// Overloaded * operator for multiplying a vector by a scalar
Vec3f Vec3f::operator*(float scalar){
	Vec3f temp;
	temp.x = this->x * scalar;
	temp.y = this->y * scalar;
	temp.z = this->z * scalar;
	return temp;
}

// Overloaded / operator for dividing a vector by a scalar
Vec3f Vec3f::operator/(float scalar){
	Vec3f temp;
	temp.x = this->x / scalar;
	temp.y = this->y / scalar;
	temp.z = this->z / scalar;
	return temp;
}

// Overloaded + operator for adding two vectors
Vec3f Vec3f::operator+(Vec3f vec){
	Vec3f temp;
	temp.x = this->x + vec.x;
	temp.y = this->y + vec.y;
	temp.z = this->z + vec.z;
	return temp;
}

// Overloaded - operator for subtracting two vectors
Vec3f Vec3f::operator-(Vec3f vec){
	Vec3f temp;
	temp.x = this->x - vec.x;
	temp.y = this->y - vec.y;
	temp.z = this->z - vec.z;
	return temp;
}



