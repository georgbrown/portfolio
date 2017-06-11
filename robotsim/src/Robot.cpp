#include "Robot.hpp"
#include <iostream>


Robot::Robot(int speedRating, int sizeRating)
    : BaseObject('r',speedRating,sizeRating){
    collideMyTarget = false;
    collideOtherTarget = false;
}


Robot::~Robot(){
}

/*! Method which returns the ID of the paired target */
int Robot::getPairedTargetID(){
    return pairedTargetID;
}

/*! Method which scans environment, collecting touch and homing readings.  Also analyzes collisions looking for 
 *  a collision with its own target */
void Robot::sensorScans(){

    typedef std::vector< std::pair<int,char> > CollideVectorPair;
    CollideVectorPair collidingObjs = env -> touchSensorReading( id );

    setFlags(collidingObjs);

    if( collideTarget ){
        analyzeTargetCollisions( collidingObjs );
    }

    // If the robot isn't colliding with anything, then it should continue homing in on target
    if(collidingObjs.size() == 0){

        std::pair<int,int> homingPair = env -> homingSensorReading( id );

        targetAngleOffset = homingPair.first;
        targetDistance = homingPair.second;

    }

}


std::pair<int,int> Robot::move( int elapsedTime ){

    int moveForward = (elapsedTime/1000.0) * speed; 

    if( collideObstacle || collideOtherTarget || collideRobot || collideWall ){

        return std::make_pair( 91 , 7*moveForward );
    }
    else{

        return std::make_pair( targetAngleOffset , moveForward );
    }
}



void Robot::pairWithTarget(int targetID ){
    pairedTargetID = targetID;
}


bool Robot::getCollideMyTarget() const{
    return collideMyTarget;
}


/*! Method analyzes the target collisions to see whether it is colliding with its own target, some other target, both, or neither */
typedef std::vector< std::pair<int,char> > CollideVectorPair; 
void Robot::analyzeTargetCollisions(CollideVectorPair collidingObjs){

    collideMyTarget = false;
    collideOtherTarget = false;

    for(CollideVectorPair::iterator it = collidingObjs.begin(); it != collidingObjs.end(); ++it){

        if( (*it).first == pairedTargetID ){
            collideMyTarget = true;
        }
        else if ( (*it).second == 't' ){
            collideOtherTarget = true;
        }
    }

}


