/**
 * \author George Brown
 *
 * \file  Robot.hpp
 * \brief Class definition for the Robot, which inherits from BaseObject. The parent is extended with
 *        implementation for target pursuit and obstacle avoidance.
 */

#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "BaseObject.hpp"
#include "Robot.hpp"


/*! Robots are special types of objects which seek out and pursue moving targets. The Robot class inherits
 *  from BaseObject, and extends it to include target pursuit functionality */
class Robot : public BaseObject {

    public:

		/*! Robot Constructor.
		 * \param speedRating A standardized speed scale rating which is used to set the actual robot speed.
		 * \param sizeRating A standardized size scale rating which is used to set the actual robot radius. */
        Robot(int speedRating, int sizeRating);
        
        
        /*! Destructor for the Robot */
        ~Robot();
    
    
        /*! Returns the ID number of the target linked to this robot (if any) */
        int getPairedTargetID();


        /*! Performs a scan of the environment to determine the trajectory needed to reach the target, as well 
         *  as to identify any possible collisions with other objects. */
        void sensorScans();


        /*! Link the robot with a particular target to pursue.
         *  \param targetID The ID of the target to link with. */
        void pairWithTarget(int targetID );


        /*! Returns a boolean collision flag which is true if the robot is colliding with its target */
        bool getCollideMyTarget() const;

    
		/*! Determines the angle to turn and the distance to travel for the robot to reach its current target.
		 *  This data is returned as a pair of integers, with the first being the angle in degrees, and the second
		 *  being the distance to the target.
		 *  \param elapsedTime The time which has elapsed (in seconds) since the last update. */
        std::pair<int,int> move( int elapsedTime );

    private:
    
        /*! ID of the target paired with the robot */
        int pairedTargetID;
        
        /*! Angle between object's current direction and the shortest path to robot */
        int targetAngleOffset;
        
        /*! Distance to the target from the robot's current location */
        int targetDistance;
        
        /*! Boolean flag which is true if the robot is currently colliding with its own target */
        bool collideMyTarget;
        
        /*! Boolean flag which is true if the robot is currently colliding with a target other than its own */
        bool collideOtherTarget;


		/*! Type definition for collision data. A vector container of pairs. The first element is the target ID number,
		 *  the second is a char which identifies the type of collision */
        typedef std::vector< std::pair<int,char> > CollideVectorPair; 
        
        
        /*! Analyzes all the objects colliding with the robot. Sets the target collision flags accordingly.
         * \param collidingObjs A vector containing all collisions identified. Each element is a pair: object ID and object type. */
        void analyzeTargetCollisions( CollideVectorPair collidingObjs );

};


#endif
