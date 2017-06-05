/**
 * \author George Brown
 *
 * \file  Target.hpp
 * \brief Class definition for the Target, which inherits from BaseObject. The parent is extended with
 *        implementation for obstacle avoidance and general movement behavior.
 */


#ifndef TARGET_HPP
#define TARGET_HPP

#include "BaseObject.hpp"
#include "Target.hpp"

/*! Targets are special types of objects which are sought out by robots. The Target class inherits from the
 *  BaseObject class and implements standard moving behavior and obstacle avoidance. */
class Target : public BaseObject{

    public:
    
		/*! Target Constructor.
		 * \param speedRating A standardized speed scale rating which is used to set the actual target speed.
		 * \param sizeRating A standardized size scale rating which is used to set the actual target radius. */
        Target(int speedRating, int sizeRating);


        /*! Target Destructor */
        ~Target();
    
    
		/*! Determines the angle to turn and the distance to travel for the next update to the target. 
		 *  This data is returned as a pair of integers, with the first being the angle in degrees, and the second
		 *  being the distance to travel.
		 *  \param elapsedTime The time which has elapsed (in seconds) since the last update. */
        std::pair<int,int> move( int elapsedTime );


        /*! Performs a scan of the environment to determine if there are any collisions with other objects. */
        void sensorScans();


    private:

};

#endif
