/**
 * \author George Brown
 *
 * \file  Obstacle.hpp
 * \brief Class definition for the Robot, which inherits from BaseObject. Currently the obstacles are not much
 *        different from the parent class in functionality, but in future iterations more sophisticated behavior
 *        may be added.
 */

#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "BaseObject.hpp"
#include "Obstacle.hpp"

/*! Obstacles are special types of objects, which create boundaries in the environment.
 *  Presently there isn't much distinction, but in future implementation the obstacle behavior may
 *  diverge more from the default objects */
class Obstacle : public BaseObject{

    public:
	
        /*! The constructor for the Obstacle
         * \param speedRating The speed setting for a newly created obstacle */
        Obstacle(int speedRating);
    
        /*! Obstacle Destructor */
        ~Obstacle();

        /*! Move the obstacle across the environment based on its current kinematics and the elapsed time.
         *  \param elapsedTime The time which has elapsed (in seconds) since the last update */
        std::pair<int,int> move( int elapsedTime );

    private:

};

#endif
