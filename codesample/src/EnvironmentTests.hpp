#include <cxxtest/TestSuite.h>

#include "Environment.hpp"
#include "BaseObject.hpp"
#include "Walls.hpp"

#include <vector>
#include <utility>
#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

class EnvironmentTests : public CxxTest::TestSuite {

public:
       void testEnvironmentProperlyCreated(void){
           Environment *env = new Environment(800,800,400);
           //test proper width
           int const expected_one = 800*400;
           int const actual_one = env->getWidth();
           TS_ASSERT_EQUALS(expected_one,actual_one);
           //test proper height
           int const expected_two  = 800*400;
           int const actual_two  = env->getHeight();
           TS_ASSERT_EQUALS(expected_two,actual_two);
       }




       void testGetWalls(void){
        Environment* env = new Environment(800,800,400);    
        Walls* walls = env->getWalls();
        //test width
        int expected_one = 800*400; 
        int actual_one = walls->getWidth();
        TS_ASSERT_EQUALS(expected_one,actual_one);
        //test height
        int expected_two = 800*400;
        int actual_two = walls->getHeight();
        TS_ASSERT_EQUALS(expected_two,actual_two); 

       }


//TODO

//
//       void testGetOrientation(void){
//         //Initialize environment with object.
//         Environment env = new Environment(10,10,2);
//         BaseObject* object = new BaseObject('r',4);
//         object->setOrientation();
//         int actual_id = env.registerObject(object);         
//
//         //Test getOrientation().
//         int expected = 15;
//         int actual = env.getObjectOrientation(actual_id);
//         TS_ASSERT_EQUALS(expected,actual);
//       }
//
//
//       void testGetObjectRadius(void){
//
//          //Initialize environment with object.
//          Environment env = new Environment(10,10,2);
//          BaseObject* object = new BaseObject('r',4);
//          object->setRadius(10);
//          int actual_id = env.registerObject(object);          
//
//          //Test for correct object radius.
//          int expected = 10; 
//          int actual = env.getObjectRadius(actual_id);
//          TS_ASSERT_EQUALS(expected,actual);
//       }
//
//       void testgetObjectType(void){
//            //Initialize environment with object.
//            Environment env = new Environment(10,10,2);
//            BaseObject* object = new BaseObject('r',2);
//            int actual_id = env.registerObject(object);
//            //Test for proper id.
//            char expected = 'r';
//            char actual = env.getObjectType(actual_id); 
//            TS_ASSERT_EQUALS(expected,actual);
//       }
//
//
//
//
//
//
//       void testGetObjectPosition(void){
//            
//            Environment env = new Environment(10,10,2);
//            BaseObject* object = new BaseObject('r',2);
//            int actual_id = env.registerObject(object);
//            
//            //test for proper position.
//            std::pair<int,int> expected = std::make_pair(10,10);
//            std::pair<int,int> actual = env.getObjectPosition(actual_id);
//            
//            TS_ASSERT_EQUALS(expected,actual);
//       }
//
//       void testGetObjectColors(void){
//            Environment env = new Environment(10,10,2);
//            BaseObject* object = new BaseObject('t',4);
//            object->setColors(2,2);
//            int actual_id = env.registerObject(object);
//            
//
//            std::pair<int,int> expected = std::make_pair(2,2);
//            std::pair<int,int> actual = env.getObjectColors(actual_id);
//
//            TS_ASSERT_EQUALS(expected,actual);
//
//
//
//       }
//
//
//       void testGetNumObjects(void){
//
//            //initialize environment with two objects
//            Environment env = new Environment(10,10,2);
//            BaseObject* object_one = new BaseObject('r',2);
//            BaseObject* object_two = new BaseObject('t',2);
//            env.registerObject(object_one);
//            env.registerObject(object_two);
//
//            //test for proper number of objects
//            int expected = 2;
//            int actual = env.getNumObjects();
//            TS_ASSERT_EQUALS(expected,actual);
//       }
//
//
//
//       //void testRegisterObject(void){
//       //  Environment
//       //}
//
//       void testgetObjectObstacleCollisionStatus(void){
//         Environment env = new Environment(10,10,2);
//         BaseObject object = new BaseObject('t',4); 
//
//         bool expected = false;
//         bool actual = true;
//         TS_ASSERT_EQUALS(expected,actual);
//
//       }
//
//       void testUpdate(void){
//         Environment env = new Environment(10,10,2);
// 
//         int expected = 1;
//         int actual = 0;
//
//         TS_ASSERT_EQUALS(expected,actual); 
//       }      
//
//       void testGetObjectIndex(void){
//         Environment env = new Environment(10,10,2);
//         BaseObject* object = new BaseObject('t',4);
//         int actual_id = env.registerObject(object);
//        
//         int expected = 0;
//         int actual = env.getObjectIndex();
//       
//         TS_ASSERT_EQUALS(expected,actual);
//
//       }
//
//
//
//
//      //void (void){}
//
//
//
//      //void (void){}
//
//
//
//      //void (void){}
//
};
