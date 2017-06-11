#include "Target.hpp"


Target::Target(int speedRating, int sizeRating)
    : BaseObject('t',speedRating, sizeRating){
}


Target::~Target(){
}


std::pair<int,int> Target::move( int elapsedTime ){

    int moveForward = (elapsedTime/1000.0) * speed;

    if( collideObstacle || collideTarget || collideRobot || collideWall ){
        return std::make_pair( 91, 7*moveForward );
    }
    else {
        return std::make_pair( 0 , moveForward );
    }
}


void Target::sensorScans(){

    typedef std::vector< std::pair<int,char> > CollideVectorPair;
    CollideVectorPair collidingObjs = env -> touchSensorReading( id );

    setFlags(collidingObjs);

}


