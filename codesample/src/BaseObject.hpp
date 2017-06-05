/**
 * \author George Brown
 *
 * \file  BaseObject.hpp
 * \brief The base class which all other physical objects derive from.
 *        It contains core data relevant to all objects, such as speed, size,
 *        color, object id number, and collision logic.
 *
 */

#ifndef BASE_OBJECT_HPP
#define BASE_OBJECT_HPP

#include <utility>
#include <tuple>
#include "Environment.hpp"

class Environment; // forward declaration

class BaseObject{

    public:

		/*! Parent constructor for all objects
		 * \param type A descriptor for the type of object inherting from the base class
		 * \param speedRating An integer control for the object's relative speed 
		*/ 
        BaseObject(char type, int speedRating);
        
        /*! Parent constructor for all objects
		 * \param type A descriptor for the type of object inherting from the base class
		 * \param speedRating An integer control for the object's relative speed
		 * \param sizeRating An integer control for the object's relative size 
		*/ 
        BaseObject(char type, int speedRating, int sizeRating);
        
        ~BaseObject();

		/*! Method which returns the object's unique ID number */
        int getID() const;
        
        /*! Method which returns the object's unique type specifier */
        char getType() const;
        
        /*! Method which rerturns the radius of the object, which is a measure of its size */
        int getRadius() const;
        
        /*! Method which returns the speed of the object */
        int getSpeed() const;
        
        /*! Method which returns a tuple containing primary and secondary color information for the object */
        std::pair<int,int> getColors() const;
        
        /*! Method which returns a static pointer to the environment which objects reside in */
        static Environment* getEnv();

		/*! Method which sets the id of the object
		 * \param id The id number to assign to the object */
        void setID(int id);
        
        /*! Method which sets the type of the object
         * \param type The type descriptor to assign to the object */
        void setType(char type);
        
        /*! Method which sets the radius of the object
         * \param radius The radius to assign to the object */
        void setRadius(int radius);
        
        /*! Method which sets a random radius for the object */
        void setRandomRadius();
        
        /*! Method which sets the speed of the object
         * \param speedRating A speed indicator which is used to set the relative object speed */
        void setSpeed(int speedRating);
        
        /*! Method which sets primary and secondary colors for the object 
         * \param primary The primary object color code
         * \param secondary The secondary object color code */
        void setColors(int primary, int secondary);

		/*! Method which sets collision data flags
		 * \param collidingObjs A vector of data pairs storing all collisions in the scene.
		 *        The first entry in each pair is the object's ID, the second is a char for its type */
        void setFlags( std::vector< std::pair<int,char> > collidingObjs );

		/*! Method which performs a sensor scan to identify objects in the scene */
        virtual void sensorScans() {};
        
        /*! Move the object across the environment by some amount in the x and y direction.
         *  The amount to move is returned as an integer pair. This is a pure virtual method which all 
         *  objects inheriting from this class must define.
         *  \param elapsedTime The amount of time which elapsed since the last update to the scene, in seconds. */
        virtual std::pair<int,int> move( int elapsedTime ) = 0;

    protected:
    
		/* The environment which the object resides in */
        static Environment* env;
        
        /* Unique data pertaining to the object */
        int id;
        int radius;
        int speed;
        char type;
        std::pair<int,int> colors;
        
        /* Object collision flags */
        bool collideWall;
        bool collideRobot;
        bool collideObstacle;
        bool collideTarget;

		/* Resets the collision flags to false */
        void resetFlags();

    private:



};

#endif
