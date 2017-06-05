#include <ctime>
#include <cstdlib>
#include "BaseObject.hpp"
#include <iostream>
#include <algorithm>

/*! Constructor for the base objects, which are parents of the other derived types.
 *  Sets the object with a random radius. */
BaseObject::BaseObject(char type, int speedRating){

    setType(type);
    setSpeed(speedRating);
    setRandomRadius();
    resetFlags();

}

/*! Constructor for base objects, which are parents of other derived types. */
BaseObject::BaseObject(char type, int speedRating, int sizeRating){

    setType(type);
    setSpeed(speedRating);
    setRadius(sizeRating);
    resetFlags();

}

/*! Destructor */
BaseObject::~BaseObject(){
}

int BaseObject::getID() const{
    return id;
}

char BaseObject::getType() const{
    return type;
}

int BaseObject::getRadius() const{
    return radius;
}

int BaseObject::getSpeed() const{
    return speed;
}

/*! Returns the primary and secondary color codes of the object, grouped into a std::pair */
std::pair<int,int> BaseObject::getColors() const{
    return colors;
}

/*! Defining the static env member variable */
Environment* BaseObject::env;

/*! Method which returns a pointer to the static environment member variable */
Environment* BaseObject::getEnv() {
    return env;
}

/*! Method which returns the type of the object.  'r' for robot, 'o' for obstacle, 't' for target */
void BaseObject::setType(char type){
    this->type = type;
}


/*! Method which sets the radius of the object based on a size rating from 0 to 100 */
void BaseObject::setRadius(int sizeRating){

    int width = env -> getWidth();
    int height = env -> getHeight();

    int dim = std::min(width,height);

	// If the input sizeRating is not within the allowed range, it is set to a default mid-range value.
    if(sizeRating < 1 || sizeRating > 100){

        std::cout << "Invalid object size choice.  Setting to 50 by default.\n";
        sizeRating = 50;
    }

	// Setting the final object radius from the environment dimensions and sizeRating
    radius = ( (0.001*sizeRating) + 0.02) * 0.7*dim;

}

/*! Method which computes a random size rating and sets the object radius accordingly */
void BaseObject::setRandomRadius(){

    setRadius( (rand() % 100) + 1 );

}


/*! Method which sets the speed of the object based on a speed rating between 0 and 100 */
void BaseObject::setSpeed(int speedRating){

    int width = env -> getWidth();
    int height = env -> getHeight();

    int dim = std::min(width,height);

    if(speedRating < 0 || speedRating > 100){

        std::cout << "Invalid object speed choice.  Setting to 50 by default.\n";
        speedRating = 50;

    }

    speed = (0.002)*speedRating*dim;

}

/*! Sets the object ID */
void BaseObject::setID(int id){
    this->id = id;
}

/*! Method which sets the primary and secondary colors of the object.  Note that these values are simply set to integers.
 *  only the graphics display cares about actual colors.  In this scope integers are sufficient since all that matters is that
 *  objects with different colors are drawn differently */
void BaseObject::setColors(int primary, int secondary){
    colors.first = primary;
    colors.second = secondary;
}

/*! Method which sets flags based on current collision values */
void BaseObject::setFlags( std::vector< std::pair<int,char> > collidingObjs ){

	// Resetting all collision flags to false
    resetFlags();

	// Each collision pair contains a char which represents the type of collision.
	// We switch on that char in a loop over all collision pairs, and set the collision flags accordingly.
    typedef std::vector< std::pair<int,char> > CollideVectorPair; 
    for(CollideVectorPair::iterator it = collidingObjs.begin(); it != collidingObjs.end(); ++it){
    
        char objType = (*it).second;

        switch( objType ){
            case 'w':
                collideWall = true;
                break;
            case 'o':
                collideObstacle = true;
                break;
            case 'r':
                collideRobot = true;
                break;
            case 't':
                collideTarget = true;
                break;
        }
    }
}

/*! Method which resets all collision flags to false */
void BaseObject::resetFlags(){

    collideWall = false;
    collideObstacle = false;
    collideRobot = false;
    collideTarget = false;

}



