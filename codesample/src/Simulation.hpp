/**
 * \author CSci3081 Instructor, George Brown
 *
 * \file  Simulation.hpp
 * \brief Main application class for the robot simulation
 *
 */

#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <vector>
#include <tuple>
#include <cmath>

#include "Walls.hpp"
#include "BaseGfxApp.hpp"
#include "Robot.hpp"
#include "Obstacle.hpp"

/** The Simulation class.  This sets up the GUI and the drawing environment. */  
class Simulation : public BaseGfxApp {
    public: 

        /*! User interface control types */
        enum UIControlType {
          UI_QUIT = 0,
          UI_START = 1,
          UI_PAUSE = 2,
          UI_RESUME = 3,
        };

        /*! The constructor for the Simulation class.  It does all setup for
         *  the display.  In particular, the initial values are set for the robot, obstacles,
         *  target, and walls.  It takes four parameters:  the number of console arguments,
         *  their values, and the width and height of the screen in pixels. 
         * \param argc The number of arguments supplied on the command line.
         * \param argv[] The values of the arguments supplied on the command line.
         * \param width The width of the screen measured in pixels.
         * \param height The height of the screen measured in pixels.
         */
        Simulation(int argc, char* argv[], int width, int height);
        virtual ~Simulation();


        /*! This public method coordinates the display at every screen refresh.  It calls the private
         *  methods which perform the actual work of drawing agents, indicators, and walls to the screen. */
        void display();   

        void gluiControl(int controlID);
        
        
        /*! Implementation of the virtual function from the base class. Handles the event of a left mouse button press.
         *  \param Mouse x position
         *  \param Mouse y position */
        void leftMouseDown(int x, int y);
        
        /*! Implemtnation of the virtual function from the base class. Handles the event of left mouse button release.
         *  \param Mouse x position
         *  \param Mouse y position */
        void leftMouseUp(int x, int y);

    private:

        /*! Pointer to the environment */
        Environment* env;

        /*! Total time (in seconds) since the simulation began */
        int totalTimeSinceStart;
        
        /*! Time (in seconds) elapsed since the previous update */
        int elapsedTime;
        
        /*! Factor by which to scale the display */
        static const int scaleFactor = 1000;

        /*! Vector containing all the color codes. Each element is an RGB tuple */
        std::vector< std::tuple < float, float, float > > colorCodesVector;

        /*! Update the rendering of everything in the environment */
        void renderEnvironment() const;
        
        
        /*! Draws the walls on the perimeter of the environment
         * \param wallWidth The spatial extent of the walls on the top and bottom borders
         * \param wallHeight The spatial extent of the walls on the left and right borders
         * \param wallThickness The thickness of all walls in the scene */
        void drawWalls(const int wallWidth, const int wallHeight, const int wallThickness) const;
        
        /*! Draw an object in the environment.
         *  \param type The type of object, specified by a single character abbreviation.
         *  \param position The (x,y) position of the object's center, grouped as a std::pair.
         *  \param radius The radius of the object.
         *  \param degree Angle by which to rotate the object model when rendering.
         *  \param colors The primary and secondary color codes, which are indices into the color codes vector.
         *  \param isCollidingWithObstacle Collision flag used to control alternative rendering when objects are colliding. */
        void drawObject(const char type, const std::pair<int,int> position, const int radius, const int degrees, 
                        const std::pair<int,int> colors, const bool isCollidingWithObstacle ) const;
                      
        /*! Sets up the color codes vector which is used for rendering */                
        void setColorCodes();

};

#endif
