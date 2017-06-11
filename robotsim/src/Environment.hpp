/**
 * \author George Brown
 *
 * \file  Environment.hpp
 * \brief The environment class contains all the physical objects in the scene and methods to register,
 *        manipulate, and destroy them. 
 *
 */
#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <vector>
#include <utility>
#include "BaseObject.hpp"
#include "Walls.hpp"

class BaseObject; // forward declaration

/** The Environment class contains a container of objects and methods for creating and desetroying them. It also
 *  Has methods for dealing with interactions between different objects.  */  
class Environment{

    public:
    
        /*! Environment constructor.
            \param width The width of the environment.
            \param height The height of the environment.
            \param scaleFactor The scaling factor which maps between pixels and distance units
         */
        Environment(const int width, const int height, const int scaleFactor);
        
        
        /*! Environment destructor */
        ~Environment();
    
    
        /*! Returns a pointer to the environment's walls for external use */
        Walls* getWalls() const;
        
    /*! Returns the width of the environment */
    int getWidth() const;

    /*! Returns the height of the environment */
    int getHeight() const;

        /*! Returns the string identifier type of a particular object in the environment, referenced by index.
         *  \param index An index into the container of objects in the environment */
        char getObjectType(const int index) const;
        
        
        /*! Returns the coordinates of a particular object in the environment, referenced by index.
         *  \param index An index into the container of objects in the environment */
        std::pair<int,int> getObjectPosition(const int index) const;
        
        
        /*! Returns the angle of orientation of a particular object in the environment, referenced by index.
         *  \param index An index into the container of objects in the environment */
        int getObjectOrientation(const int index) const;
        
        
        /*! Returns the radius of a particular object in the environment, referenced by index.
         * \param index An index into the container of objects in the environment */
        int getObjectRadius(const int index) const;
        
        
        /*! Returns the primary and secondary colors of an object in the environment, referenced by index.
         * \param index An index into the container of objects in the environment */
        std::pair<int,int> getObjectColors(const int index) const;
        
        
        /*! Returns the object-obstacle collision status of a particular object in the environment, referenced by index.
         * \param index An index into the container of objects in the environment */
        bool getObjectObstacleCollisionStatus(const int index) const;
    
    
        /*! Returns the number of objects registered with the environment */
        int getNumObjects() const;
      
        
        /*! Registers an object with the environment.  
         * \param objPtr A pointer to an object which is to be registered with the environment. */
        int registerObject( BaseObject* objPtr);
        
        
        /*! Update the physical state of everything in the environment.
         *  \param elapsedTime The amount of time (in seconds) which has elapsed since the last update */
        void update(int elapsedTime);     
    
    
        /*! Detects whether a given object in the environment is colliding with any other object in the environment. 
            \param objID The id number of the object whose collision status is to be determined */
        typedef std::vector< std::pair<int,char> > CollideVectorPair;
        CollideVectorPair touchSensorReading( int objID );

    
        /*! Determines the angle and distance an object in the environment must rotate and move by to reach its target
         * \param robotID The id number of the robot in the environment which seeks out targets */
        typedef std::pair<int,int> HomingPair;
        HomingPair homingSensorReading( int robotID );

    private:

        class ObjectData{

            public:
            
                /*! Constructor for ObjectData
                \param id The identification number.
                \param type The type of object.
                \param radius The radius of the object. */ 
                ObjectData(int id, char type, int radius);
                
                
                /*! Destructor */        
                ~ObjectData();
                
                
                /*! Returns the current x position of the Object in pixels. */
                int getXPosition() const;
                
                
                /*! Returns the current y position of the Object in pixels. */                
                int getYPosition() const;
                
                
                /*! Returns the current orientation of the Object in degrees. */           
                int getOrientation() const;
                
                
                /*! Returns the current radius of the Object in pixels. */
                int getRadius() const;
                
                
                /*! Returns the current ID of the Object in pixels. */
                int getID() const;
              
              
                /*! Returns the collision status of an object-obstacle interaction */
                bool getObstacleCollisionStatus() const;
                
                
                /*! Returns the type specifier of the object */
                char getType() const;
                
                
                /*! Sets a new (x,y) position of the object
                    \param x The new x position of the object in pixels.
                    \param y The new y position of the object in pixels.
                */
                void setPosition(int x, int y);
                
                
                /*! Sets a new angle of orientation for the object
                    \param degrees The new orientation of the object in degrees.
                */          
                void setOrientation(int degrees);
                
                
                /*! Changes the radius of the Object.
                    \param radius The new radius of the object in pixels.  */ 
                void setRadius(int radius);
                
                
                /*! Sets the ID of the Object.
                    \param ID The new ID of the object.
                */ 
                void setID(int id);
                
                
                /*! Changes the object-obstacle collision status.
                 *  \param status The new collision status to be set */
                void setObstacleCollisionStatus(bool status);
                
                
                /*! Changes the type of the object.
                    \param ID The new type specifier for the object */
                void setType(char type);
                
                
                /*! Rotate the object by a given amount of degrees.
                 *  \param degrees The number of degrees by which to rotate the object */
                void rotate( int degrees );
                
                
                /*! Translates the object across the environment by a given amount in the direction it currently faces.
                 *  \param moveForward The amount by which to translate the object in its current direction of travel. */
                void translate( int moveForward );


            private:
            
                /*! The current x position of the object, in pixels. */
                int x;
                
                 /*! The current y position of the object, in pixels. */
                int y;
                
                /*! The current orientation of the object, in degrees. */
                int degrees;
                
                /*! The current radius of the object, in pixels. */
                int radius;
                
                /*! The identification number of the object */
                int id;
                
                /*! Object-obstacle collision flag */
                bool isCollidingWithObstacle;
                
                /*! Object type specifier */
                char type;
                
                /*! This method places the object at a random collision-free location in the environment */
                void setRandomPosition();

        }; // end of inner-class ObjectData
        
        
        /*! A pair which groups an object pointer and associated meta-data into one entity */
        typedef std::vector< std::pair< BaseObject*, ObjectData* > > ObjVectorPair;
        
        /*! Collection of all grouped objects & data in the environment */
        static ObjVectorPair objects;
        
        /*! Walls which form the boundaries of the environment */
        static Walls* walls;
        
        /*! Environment width */
        static int width;
        
        /*! Environment height */
        static int height;


        /*! Returns a pointer to an object in the environment, referenced by identification number
         *  \param objectID The ID number of the object whose pointer is requested */
        BaseObject* getObject( int objectID );
        
        
        /*! Returns the index into the environment's object collision which matches a given ID number
         *  \param objectID The ID number of the object whose index in the object collision is requested */
        int getObjectIndex( int objectID );
        
        
        /*! Returns a pointer to assosicated object meta-data, referenced by identification number
         *  \param objectID The ID number of the object whose meta-data is requested */
        ObjectData* getObjectData( int objectID );
       
       
        /*! Helper function which checks to see whether or not two given circles are in an overlapping state.
         * \param x1 The X-position of the first circle.
         * \param y1 The Y-position of the first circle.
         * \param r1 The radius of the first circle.
         * \param x2 The X-position of the second circle.
         * \param y2 The Y-position of the second circle.
         * \param r2 The Radius of the second circle. */
        static bool circlesOverlap(int x1, int y1, int r1, int x2, int y2, int r2);


}; // end of class Environment



#endif
