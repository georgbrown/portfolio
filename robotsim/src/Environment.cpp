
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "Environment.hpp"
#include "Robot.hpp"
#include "Obstacle.hpp"
#include "Target.hpp"
#include <iostream>

/*! Constructor for Environment takes two arguments, the width and height of the environment */
Environment::Environment(const int width, const int height, const int scaleFactor){

    this->width = width*scaleFactor;
    this->height = height*scaleFactor;

    /*! Constructing walls with given environment dimensions */
    walls = new Walls(this->width,this->height);

    /*! Setting the numbers of robots, targets, and obstacles in the env */
    const int numRobots = 2;
    const int numTargets = 2;
    const int numObstacles = 6;

    std::vector<int> openTargetIDs;
    int id;

    /*! Creating and registering the obstacles */
    for(int i = 0; i < numObstacles; i++){

        Obstacle* obstacle = new Obstacle(0);
        id = registerObject( obstacle );
        obstacle -> setColors(0,0);
    }

    /*! Creating and registering the targets */
    for(int i = 0; i < numTargets; i++){

        Target* target = new Target(35,25);
        id = registerObject( target );
        target -> setColors(id,id); 
        openTargetIDs.push_back( id );
    }


    /*! Creating and registering the robots */
    for(int i = 0; i < numRobots; i++){
    
        Robot* robot = new Robot(50,30);
        id = registerObject( robot );
        robot = dynamic_cast<Robot*>( getObject( id ) );
        if( openTargetIDs.size() > 0 ){
            robot -> pairWithTarget( openTargetIDs.back() );
            robot -> setColors(1, robot->getPairedTargetID() ); 
            openTargetIDs.pop_back();
        }
    }

}


/*! Destructor for the Environment */
Environment::~Environment(){
}

/*! Returns the width of the Environment */
int Environment::getWidth() const{
    return width;
}

/*! Returns the height of the environment */
int Environment::getHeight() const{
    return height;
}

/*! Returns a pointer to the walls */
Walls* Environment::getWalls() const{
    return walls;
}

/*! Returns the type of a particular object.  Objects are stored in some hidden
 *  data structure.  This method accesses the objects by index in that data structure */
char Environment::getObjectType(const int index) const{

    ObjectData* objDataPtr = ( objects.at(index) ).second;
    return objDataPtr->getType(); 
}

/*! Returns the position of a particular object(X,Y).  Objects are stored in some hidden
 *  data structure.  This method accesses the objects by index in that data structure */
std::pair<int,int> Environment::getObjectPosition(const int index) const{

    ObjectData* objDataPtr = ( objects.at(index) ).second;
    const int x = objDataPtr->getXPosition();
    const int y = objDataPtr->getYPosition();

    return std::make_pair( x , y );
}

/*! Returns the angle of orientation of a particular object.  Objects are stored in some hidden
 *  data structure.  This method accesses the objects by index in that data structure */
int Environment::getObjectOrientation(const int index) const{

    ObjectData* objDataPtr = ( objects.at(index) ).second;
    return objDataPtr->getOrientation();
}

/*! Returns the radius of a particular object.  Objects are stored in some hidden
 *  data structure.  This method accesses the objects by index in that data structure */
int Environment::getObjectRadius(const int index) const{
    
    ObjectData* objDataPtr = ( objects.at(index) ).second;
    return objDataPtr->getRadius();
}
/*! Returns the color  of a particular object.  Objects are stored in first 
 *  data structure.  This method accesses the objects by index in that data structure */
std::pair<int,int> Environment::getObjectColors(const int index) const{

    BaseObject* objPtr = ( objects.at(index) ).first;
    return objPtr->getColors();
}

/*! Returns the obstacle collision status of a particular object.  Objects are stored in some hidden
 *  data structure.  This method accesses the objects by index in that data structure */
bool Environment::getObjectObstacleCollisionStatus(const int index) const{

    ObjectData* objDataPtr = ( objects.at(index) ).second;
    return objDataPtr -> getObstacleCollisionStatus();
}


/*! Returns the number of objects registered with the environment */
int Environment::getNumObjects() const{
    return objects.size();
}



/*! Registers an object with the environment.  A pointer to the object is passed to this function
 *  An internal data structure is set up to store information about that object.  A pair of pointers
 *  movement pair.  One pointer is to the object itself, the other pointer is to the object's data.
 */
int Environment::registerObject( BaseObject* objPtr ){

    // IDs start as 4 so that in future implementation each wall will refer to 0, 1, 2, and 3.
    static int newID = 4;

    objPtr->setID(newID);
    const char type = objPtr->getType();
    const int radius = objPtr->getRadius();
    ObjectData* objDataPtr = new ObjectData( newID, type, radius );

    // If the object is a target then it's orientation is initialized at random
    if( type == 't' ){    
        objDataPtr -> setOrientation( rand() % 360 );
    }
    else{
        objDataPtr -> setOrientation( 0 );
    }

    newID++;

    // Storing the data record in the vector of objects
    objects.push_back( std::make_pair ( objPtr , objDataPtr ) );

    return newID - 1;

}


/*! Update situation with the environment.  A pointer to the environment is setting to this function
 *  An internal data structure is based on the amount of time that passed since the last update.  A pair of pointers
 *  the movement pair. According to type. looping over all object to move and to update position.
*/
//TODO: Implement the update method which updates all the object positions
void Environment::update( int elapsedTime ){

    Robot* robotPtr;
    Target* targetPtr;
    ObjectData* objDataPtr;
    std::pair<int,int> movementPair;

    // Looping over all objects so they may perform sensor scans
    for(ObjVectorPair::iterator it = objects.begin(); it != objects.end(); ++it){

        char type = ((*it).first) -> getType();

        switch( type ){
            case 'r':
                robotPtr = dynamic_cast<Robot*>( (*it).first );
                robotPtr -> sensorScans();
                break;
            case 't':
                targetPtr = dynamic_cast<Target*>( (*it).first );
                targetPtr -> sensorScans();
                break;
            case 'o':
            default:
                break;
        }
    }

    // Creating a vector to house objects marked to be deleted
    std::vector<int> objsToDelete; 

    // Deleting robot-target pairs that have collided
    for(ObjVectorPair::iterator it = objects.begin(); it != objects.end(); ++it){
    
        char type = ((*it).first) -> getType();
        if( type == 'r' ){
            robotPtr = dynamic_cast<Robot*>( (*it).first );

            if( robotPtr -> getCollideMyTarget() ){

                objsToDelete.push_back( robotPtr -> getID() );
                objsToDelete.push_back( robotPtr -> getPairedTargetID() );
            }
        }
    }

    // Iterating through vector of marked objs and erasing them
    for(int i = 0; i < static_cast<int>( objsToDelete.size() ); i++){

        int objID = objsToDelete.at(i);
        int index = getObjectIndex( objID );
        objects.erase( objects.begin() + index );
    }
        

    // Iterating through the objects and moving them based on elapsedTime
    for(ObjVectorPair::iterator it = objects.begin(); it != objects.end(); ++it){

        char type = ((*it).first) -> getType();
        objDataPtr = (*it).second;

        switch( type ){
            case 'r':
                robotPtr = dynamic_cast<Robot*>( (*it).first );
                movementPair = robotPtr -> move( elapsedTime );
                break;

            case 't':
                targetPtr = dynamic_cast<Target*>( (*it).first );
                movementPair = targetPtr -> move( elapsedTime );
                break;

            case 'o':
            default:
                break;
        }

        objDataPtr -> rotate( movementPair.first );
        objDataPtr -> translate( movementPair.second );

    }   

}

/*! Colliding anything  with the environment. Storing the position and radius about the current object.
 *  For colliding Objects are  stored in some hidden data structure. Colliding object can be changing continuously because of random.
 *  Accordingly to change ID. An internal data structure is set up to store information about object collision status
 *  Checking ID and the robot is overlapping the wall or antoehr object. A pointer to the colliding object is passed to this function
 *  An internal data structure store colliding information.
*/
typedef std::vector< std::pair<int,char> > CollideVectorPair;

CollideVectorPair Environment::touchSensorReading( int objID ){
   
    ObjectData* objDataPtr = getObjectData( objID );
    objDataPtr -> setObstacleCollisionStatus( false );
              
    /*! Locally storing the position and radius into about the object */
    const int typeObj = objDataPtr -> getType();
    const int xObj = objDataPtr -> getXPosition();
    const int yObj = objDataPtr -> getYPosition();
    const int rObj = objDataPtr -> getRadius();

    CollideVectorPair collidingObjs;

    /*! Iterating through all objects and comparing their data to the original object */
    for(ObjVectorPair::iterator it = objects.begin(); it != objects.end(); ++it){
        
        const int otherID = (*it).second -> getID();
        const int typeOther = (*it).second -> getType();
        const int xOther = (*it).second -> getXPosition();
        const int yOther = (*it).second -> getYPosition();
        const int rOther = (*it).second -> getRadius();

        if( ( objID != otherID ) && circlesOverlap( xObj, yObj, rObj, xOther, yOther, rOther ) ){

            collidingObjs.push_back( std::make_pair( otherID , typeOther ) );

            if( typeObj == 'r' && typeOther == 'o' ){
                objDataPtr -> setObstacleCollisionStatus( true );
            }
        }  
    }

    /*! Wall attributes are obtained */
    const int thickness = walls->getThickness();
    const int width = walls->getWidth();
    const int height = walls->getHeight();

    /*! Each wall is checked to determine whether the agent is inside or not */
    const bool insideLeftWall = (xObj - rObj) <= thickness;
    const bool insideRightWall = (xObj + rObj) >= (width - thickness);
    const bool insideBottomWall = (yObj - rObj) <= thickness;
    const bool insideTopWall = (yObj + rObj) >= (height - thickness);

    /*! Returns true if any of the walls overlapped the agent */
    if (insideLeftWall || insideRightWall || insideBottomWall || insideTopWall){
        collidingObjs.push_back( std::make_pair( 1 , 'w' ) );
    }

    return collidingObjs;
           
}


/*! Homing the target with the environment. The amount must rotate and move forward to reach the target.
 *  Checking the target position and the robot position. Calculating the theta using atan2.
 *  Making targetAngleOffset. Also, calculate the distance between target and robot.
 *  Return distance and direction from target.
*/
std::pair<int,int> Environment::homingSensorReading( int robotID ){

    Robot* robotPtr = dynamic_cast<Robot*>( getObject( robotID ) );
    ObjectData* robotDataPtr = getObjectData( robotID );

    int targetID = robotPtr -> getPairedTargetID();
    ObjectData* targetDataPtr = getObjectData( targetID );
    
    int xRobot = robotDataPtr -> getXPosition();
    int yRobot = robotDataPtr -> getYPosition();

    int xTarget = targetDataPtr -> getXPosition();
    int yTarget = targetDataPtr -> getYPosition();

    int theta = (57.2957795*atan2( yTarget - yRobot , xTarget - xRobot ));
    int targetAngleOffset = theta - robotDataPtr -> getOrientation();
    int distToTarget = sqrt( pow( ( yTarget - yRobot ) , 2) + pow( ( xTarget - xRobot ) , 2) );   

    return std::make_pair( targetAngleOffset , distToTarget );
}



/*! Returns the getting object.  Objects is showed in first 
 *  data structure.  This method accesses the objects ID in that data structure */
BaseObject* Environment::getObject( int objectID ){

    for(ObjVectorPair::iterator it = objects.begin(); it != objects.end(); ++it){
    
        if( (*it).first -> getID() == objectID ){
            return (*it).first;
        }
    }
    
    std::cout << "No ID match.  Object not found.\n";
    exit(1);

}

/*! Method returns the index in the data structure in which an object with the given ID resides */
int Environment::getObjectIndex( int objectID ){

    int index = -1;

    for(int i = 0; i < static_cast<int>( objects.size() ); i++){
        if( ( (objects.at(i)).first -> getID() ) == objectID){
            index = i;
        }
    }
    return index; 
}


/*! Returns a pointer to the object's data.  Objects are stored in some hidden
 *  data structure.  This method accesses the objects ID in that
 *  hidden data structure */
Environment::ObjectData* Environment::getObjectData( int objectID ){

    for(ObjVectorPair::iterator it = objects.begin(); it != objects.end(); ++it){

        if( (*it).first -> getID() == objectID ){
            return (*it).second;
        }
    }

    std::cout << "No ID match.  Object not found.\n";
    exit(1);
}


/*! Method which returns true if two circles are overlapping */
bool Environment::circlesOverlap(int x1, int y1, int r1, int x2, int y2, int r2) {

    return ( sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) - ( r1 + r2 ) ) <= 0; 
}


////////////////////////////  INNER CLASS METHODS ///////////////////////////////

/*! Setting getter and setter about the Evicorment Class */
Environment::ObjectData::ObjectData(int id, char type, int radius){
    setID(id);
    setType(type);
    setRadius(radius);
    setRandomPosition();
}

/*! Destructor */
Environment::ObjectData::~ObjectData(){
}

/*! Returns the current x position of the Object in pixels. */
int Environment::ObjectData::getXPosition() const {
    return x;
}

/*! Returns the current y position of the Object in pixels. */                
int Environment::ObjectData::getYPosition() const {
    return y;
}

/*! Returns the current orientation of the Object in degrees. */           
int Environment::ObjectData::getOrientation() const {
    return degrees;
}

/*! Returns the current radius of the Object in pixels. */
int Environment::ObjectData::getRadius() const {
    return radius;
}

/*! Returns the current ID of the Object in ID. */
int Environment::ObjectData::getID() const {
    return id;
}

/*! Finding collisions between object and obstacle. 
Returns true if the Object is colliding with object or obstacle, 
returns false otherwise.
*/
bool Environment::ObjectData::getObstacleCollisionStatus() const {
    return isCollidingWithObstacle;
}

/*! Returns the type of the object. */
char Environment::ObjectData::getType() const {
    return type;
}


/*! Sets object position based on input x and y */
void Environment::ObjectData::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}


/*! Sets object orientation */
void Environment::ObjectData::setOrientation(int degrees) {
    this->degrees = ( (degrees % 360) + 360 ) % 360;
}

/*! Sets the object radius */
void Environment::ObjectData::setRadius(int radius) {
    this->radius = radius;
}

/*! Sets the ID of the Object.*/ 
void Environment::ObjectData::setID(int id) {
    this->id = id;
}

/*! Method which updates the collision status of an object with an obstacle */
void Environment::ObjectData::setObstacleCollisionStatus(bool status) {
    isCollidingWithObstacle = status;
}

/*! Sets the object type */
void Environment::ObjectData::setType(char type) {
    this->type = type;
}

/*! Rotates the object by a given amount */
void Environment::ObjectData::rotate( int rotateDegrees ){
    setOrientation( degrees + rotateDegrees );
}

/*! Translates the object a given amount forward */
void Environment::ObjectData::translate( int moveForward ){

    float radians = 0.01745329 * degrees;
    int xMove = moveForward*cos(radians);
    int yMove = moveForward*sin(radians);

    setPosition(x + xMove , y + yMove);

}

/*! Method which sets the object's position in the environment at random */
void Environment::ObjectData::setRandomPosition(){

    /*! Computing the workable area */
    const int enclosureWidth = ( walls->getWidth() - 2*walls->getThickness() );
    const int enclosureHeight = ( walls->getHeight() - 2*walls->getThickness() );

    /*! Attempting to place the object in the movable area */
    int numAttempts = 0;
    bool isTouching;

    do
    {
        /*! Assume nothing is touching this object yet */
        isTouching = false;
        numAttempts++;

        /*! Generating random x and y values for the agent to be placed at */
        x = ( rand() % ( enclosureWidth - 2*radius ) ) + radius + walls->getThickness();
        y = ( rand() % ( enclosureHeight - 2*radius ) ) + radius + walls->getThickness();

        /*! Iterating through all the objects in the vector of objects */
        for(ObjVectorPair::iterator it = objects.begin(); it != objects.end(); ++it){

            int x2 = (*it).second -> getXPosition();
            int y2 = (*it).second -> getYPosition();
            int r2 = (*it).second -> getRadius();

            /*! Determining whether the random (x,y) is valid based on other objects locations */
            if( circlesOverlap(x, y, radius, x2, y2, r2) ){
                isTouching = true;
            }
        }
        
      /*! Continue looping and trying new (x,y) positions until a valid one is found */
    } while ( isTouching && ( numAttempts < 100 ) );

}

//////////////  STATIC VAR DEFINITIONS /////////////////////

int Environment::width;
int Environment::height;

Walls* Environment::walls;
std::vector< std::pair<BaseObject* , Environment::ObjectData* > > Environment::objects;


