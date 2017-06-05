#include "Obstacle.hpp"

Obstacle::Obstacle(int speedRating)
    : BaseObject('o',speedRating){
}

Obstacle::~Obstacle(){
}

/*! Method which currently "moves" the obstacle by doing nothing.  In the future there may be
 *  moving objects at which point this method will be more fully implemented */
std::pair<int,int> Obstacle::move( int elapsedTime ){

    /*!Setting the variable of rotate Degree and moveForward.*/
    int rotateDegrees = 0;
    int moveForward = 0;

    /*!Returen to pair structure.*/
    return std::make_pair( rotateDegrees , moveForward );


}


