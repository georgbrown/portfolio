/**
 * \author George Brown
 *
 * \file Math.hpp 
 * \brief Custom math classes are defined for dealing with mathematical
 *        vectors in 2 and 3 dimensions.
 */


#ifndef MATH_HPP
#define MATH_HPP

#include <string>
#include <sstream>
#include <cmath>

/*! \class Vec2i Custom vector class which stores two integers */
class Vec2i {

	public:

		/*! Vec2i constructor. Intializes x and y to 0 */
		Vec2i() : x(0), y(0) {}
		
		/*! Vec2i constructor with input arguments.
		 * \param x_ The intial x integer value.
		 * \param y_ The initial y integer value. */
		Vec2i( int x_, int y_ ) : x(x_), y(y_) {}
		
		/*! The x component */
		int x;
		
		/*! The y component */
		int y;
		
		/*! Converts the vector to a string for text output
		 * \return Vec2i as a string */
		std::string to_str() const;
		
}; // end class Vec2i


/*! \class Vec3i Custom vector class which stores three integers */
class Vec3i {
	
	public:
		
		/*! Vec3i constructor. Initializes x, y, and z to 0. */
		Vec3i() : x(0), y(0), z(0) {}
		
		/*! Vec3i constructor with input arguments.
		 * \param x_ The initial x integer value.
		 * \param y_ The initial y integer value.
		 * \param z_ The initial z integer value. */
		Vec3i( int x_, int y_, int z_ ) : x(x_), y(y_), z(z_) {}

		/*! The x component */
		int x;
		
		/*! The y component */
		int y;
		
		/*! The z component */
		int z;
		
		/*! Converts the vector to a string for text output
		 * \return Vec3i as a string */
		std::string to_str() const;
		
}; // end class Vec3i


/*! \class Vec2f Custom vector class which stores two floats */
class Vec2f {
	
	public:
	
		/*! Vec2f constructor. Initializes x and y to 0. */
		Vec2f() : x(0), y(0) {}
		
		/*! Vec2f constructor with input arguments.
		 * \param x_ The initial x float value.
		 * \param y_ The initial y float value. */
		Vec2f( float x_, float y_ ) : x(x_), y(y_) {}
		
		/*! The x component */
		float x;
		
		/*! The y component */
		float y;
		
		/*! Converts the vector to a string for text output
		 * \return Vec2f as a string */
		std::string to_str() const;
		
}; // end class Vec2f


/*! \class Vec3f Custom vector class which stores three floats */
class Vec3f {

	public:

		/*! Vec3f constructor. Initializes x, y, and z to 0. */
		Vec3f() : x(0), y(0), z(0) {}
		
		/*! Vec3f constructor with input arguments.
		 * \param x_ The initial x float value.
		 * \param y_ The initial y float value.
		 * \param z_ The initial z float value. */
		Vec3f( float x_, float y_, float z_ ) : x(x_), y(y_), z(z_) {}
		
		/*! Computes the cross product of two vectors.
		 * \param v1 The first input vector.
		 * \param v2 The second input vector.
		 * \return Cross product of v1 and v2 */
		static Vec3f cross(Vec3f v1, Vec3f v2);
		
		/*! Computes the dot product of two vectors.
		 * \param v1 The first input vector.
		 * \param v2 The second input vector.
		 * \return Dot product of v1 and v2 */
		static float dot(Vec3f v1, Vec3f v2);
		
		/*! Computes and returns the normalized input vector.
		 * \param vec The vector to be normalized
		 * \return Normalized vec */
		static Vec3f normalize(Vec3f vec);
		
		/*! Computes the norm of a vector.
		 * \param vec The vector whose norm is to be computed.
		 * \return Norm of vec */
		static float norm(Vec3f vec);
		
		/*! Clamps the components of a vector between min and max values.
		 * \param vec The vector to be clamped
		 * \param valMin The lower bound for clamping
		 * \param valMax The upper bound for clamping
		 * \return Result of clamping vec between valMin and valMax */
		static Vec3f clamp(Vec3f vec, float valMin, float valMax);
	
		/*! Overloaded * operator for multiplying a vector by a scalar
		 * \param scalar The scalar value to multiply the vector by
		 * \return Vector with each component multiplied by scalar */
		Vec3f operator*(float scalar);
		
		/*! Overloaded / operator for dividing a vector by a scalar
		 * \param scalar The scalar value to divide the vector by 
		 * \return Vector with each component divided by scalar */
		Vec3f operator/(float scalar);
		
		/*! Overloaded + operator for adding two vectors 
		 * \param vec The vector to perform the addition with
		 * \return Summation of the two vectors */
		Vec3f operator+(Vec3f vec);
		
		/*! Overloaded - operator for subtracting two vectors
		 * \param vec The vector to perform the subtraction with
		 * \return Difference of the two vectors */
		Vec3f operator-(Vec3f vec);
	
		/*! The x component */
		float x;
		
		/*! The y component */
		float y;
		
		/*! The z component */
		float z;
		
		/*! Converts the vector to a string for text output
		 * \return Vec3f as a string */
		std::string to_str() const;
	
}; // end class Vec3f

/*! Scalar-vector multiplication, overloading the * operator.
 *  \param scalar The scalar value to multipy the vector by
 *  \param rhs The vector being multiplied
 *  \return Result of scalar-vector multiplication */
inline Vec3f operator*(float scalar, Vec3f rhs){
	return rhs * scalar;
}


/*! Dividing a vector by a scalar, overloading the / operator.
 *  \param scalar The scalar value to divide the vector by
 *  \param rhs The vector being divided 
 *  \return Result of scalar-vector division */
inline Vec3f operator/(float scalar, Vec3f rhs){
	return rhs / scalar;
}


#endif
