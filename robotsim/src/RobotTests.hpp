#include <cxxtest/TestSuite.h>

#include "Environment.hpp"
#include "BaseObject.hpp"
#include "Robot.hpp"
#include "Target.hpp"
#include "BaseObject.hpp"

#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

class RobotTests : public CxxTest::TestSuite {

public:
      void testGetPairedTarget(void){
//          Environment* env = new Environment(800,800,400);
//          Robot robot (1,1);
//          BaseObject* target = new BaseObject('t',4);
//          int target_id = env->registerObject(target);
//          robot.pairWithTarget(target_id);
//          env->registerObject(robot);
          
//          int expected = target_id;
//          int actual = robot.getPairedTargetID();
            //TODO
            bool expected = true;
            bool actual = false;
            TS_ASSERT_EQUALS(expected,actual);
      }

      void testSensorScans(void){


        //TODO
      }

      void testPairWithTarget(void){
        //TODO
      }

      void testGetCollideMyTarget(void){

         //TODO

      }
      
      void testMove(void){


        //TODO


      }


}; 
