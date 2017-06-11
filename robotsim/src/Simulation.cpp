#include "Simulation.hpp"
#include <iostream>

#define PI 3.1415926535f

Simulation::Simulation(int argc, char* argv[], int width, int height) : BaseGfxApp(argc, argv, width, height, 50, 50, GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH, true, 851, 50) {
    setCaption("Robot Simulation");

    //creates a basic UI panel with quit button
    GLUI_Panel *toolPanel = new GLUI_Panel(m_glui, "Control Panel");
    new GLUI_Button(m_glui, "Quit", UI_QUIT, (GLUI_Update_CB)exit);
//    new GLUI_Button(m_glui, "Start", UI_START, (GLUI_Update_CB)start);
//    new GLUI_Button(m_glui, "Pause", UI_PAUSE, (GLUI_Update_CB)pause);
//    new GLUI_Button(m_glui, "Resume", UI_RESUME, (GLUI_Update_CB)resume);
              
    // Initialize OpenGL
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glEnable(GL_BLEND); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
    gluOrtho2D(0, m_width, 0, m_height);
    glViewport(0, 0, m_width, m_height);

    /*! Creating the environment */
    env = new Environment( width, height, scaleFactor );

    setColorCodes();

}

void Simulation::gluiControl(int controlID){
    // nothing here for now.
}


void Simulation::display(){    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /*! Updating the time counters keeping track of total time
     *  since the simulation began as well as the elapsed time since
     *  the last update. */
    int newTotalTime = glutGet(GLUT_ELAPSED_TIME);
    elapsedTime = newTotalTime - totalTimeSinceStart;
    if(elapsedTime > 30){
        totalTimeSinceStart = newTotalTime; 

        /*! Updating the true environment based on the time since the last update */
        env->update( elapsedTime );

        /*! Updating the environment as depicted in the simulation screen */
        renderEnvironment();

        // debugging messages
        int err;
        if ((err = glGetError()) != GL_NO_ERROR) {
            cerr << "GL is in an error state" << endl;
            cerr << "(GL error code " << err << ")\n";
            assert(0);
        }
        
        // advance
        glutSwapBuffers();

    }
}


Simulation::~Simulation(){
}

void Simulation::leftMouseDown(int x, int y){
    // nothing here for now
}

void Simulation::leftMouseUp(int x, int y){
    // nohing here for now
}


/*! Method responsible for rendering the entire environment.
 *  Draws the walls as well as all the objects to the screen
*/
void Simulation::renderEnvironment() const{

    // Computing inverse scale factor so the environment may be downscaled to a drawn window
    const float inverseScaleFactor = 1.0 / scaleFactor;

    // Collecting wall information
    const Walls* walls = env->getWalls();
    const int wallThickness = (walls->getThickness()) * inverseScaleFactor;
    const int wallHeight = (walls->getHeight()) * inverseScaleFactor;
    const int wallWidth = (walls->getWidth()) * inverseScaleFactor;

    drawWalls(wallWidth,wallHeight,wallThickness);

    std::pair<int,int> position;
    std::pair<int,int> colors;
    int degrees;
    int radius;
    bool isCollidingWithObstacle;
    char type;

    /*! Looping through all the objects registered to the environment.
     *  Object data is collected and is then used to draw. */
    for(int i=0; i < env->getNumObjects(); i++){

        type = env->getObjectType(i);

        position = env->getObjectPosition(i);
        position.first *= inverseScaleFactor;
        position.second *= inverseScaleFactor;

        degrees = env->getObjectOrientation(i);

        radius = ( env->getObjectRadius(i) ) * inverseScaleFactor;

        colors = ( env -> getObjectColors(i) );

        isCollidingWithObstacle = env -> getObjectObstacleCollisionStatus(i);

        drawObject(type, position, radius, degrees, colors, isCollidingWithObstacle);
    }
}


/*! Method to draw the walls on all four sides of the screen */
void Simulation::drawWalls( const int wallWidth, const int wallHeight, const int wallThickness ) const{
    
    // Making the walls grey
    glColor3f(0.5,0.5,0.5);

    /*! Drawing each of the four walls */
    glRecti( 0, 0, wallThickness, wallHeight );
    glRecti( wallWidth - wallThickness, 0, wallWidth, wallHeight );
    glRecti( wallThickness, 0, wallWidth - wallThickness, wallThickness );
    glRecti( wallThickness, wallHeight - wallThickness, wallWidth - wallThickness, wallHeight );

}


/*! Method to draw objects.  Each object is drawn differently depending on its type. */
void Simulation::drawObject(const char type, const std::pair<int,int> position, const int radius, const int degrees, std::pair<int,int> colors, bool isCollidingWithObstacle ) const{

    std::tuple<float,float,float> rgbColors;
    float red;
    float green;
    float blue;
    int glColorIndex;

    // Based on object information different colors are used to draw it
    switch( type ){

        case 'o':
            glColor3f(0.0, 0.0, 1.0);
            break;

        case 'r':
            if ( isCollidingWithObstacle ){
                glColor3f(1.0, 0.75, 0.0);
            }
            else{
                glColor3f(1.0,1.0,0.0);
            }
            break;

        case 't':

            // Getting the target's primary color and mapping it to an openGL color code
            glColorIndex = ( colors.first % colorCodesVector.size() );

            rgbColors = colorCodesVector.at( glColorIndex );

            red = std::get<0>( rgbColors );
            green = std::get<1>( rgbColors );
            blue = std::get<2>( rgbColors );

            glColor3f(red,green,blue);

            break;

        default:
            glColor3f(0.5, 0.5, 0.5);
    }

    const int x = position.first;
    const int y = position.second;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x,y);
    const int numTri = 100; // number of triangles used to draw circle
    for(int i = 0; i<= numTri; i++){
        glVertex2f(
            (x + radius * cos( i*2.0*PI / static_cast<float>(numTri))),
            (y + radius * sin( i*2.0*PI / static_cast<float>(numTri)))
        );
    }
    glEnd();

    /*! If the object is of type robot, then an indicator will be drawn too */
    if(type == 'r'){

        /*! Computing the agent's current angle in radians to be used by trig functions.
         *  Also setting the indicator length to be 150% of the agent's radius */
        const float radians = (static_cast<float>(degrees)/180.0)*PI;
        const float indicatorLength = 1.5*radius;

        /*! Setting a thicker line width and getting a color code matching this robot's target */
        glLineWidth(2.0f);
        glColorIndex = ( colors.second % colorCodesVector.size() );
        red = std::get<0>( colorCodesVector.at( glColorIndex ) );
        green = std::get<1>( colorCodesVector.at( glColorIndex ) );
        blue = std::get<2>( colorCodesVector.at( glColorIndex ) );
        glColor3f(red, green, blue);

        /*! Constructing the line segment */
        glBegin(GL_LINES);
        glVertex2f(x,y);
        glVertex2f(x + indicatorLength*cos(radians) , y + indicatorLength*sin(radians) );
        glEnd();       
    }

}

/*! Method which registers colors by storing them in a vector of tuples of RGB values. */
void Simulation::setColorCodes(){

    colorCodesVector.push_back( std::make_tuple( 1.0, 0.0, 0.0 ) ); // red
    colorCodesVector.push_back( std::make_tuple( 0.0, 1.0, 0.0 ) ); // green
    colorCodesVector.push_back( std::make_tuple( 1.0, 0.0, 1.0 ) ); // magenta
    colorCodesVector.push_back( std::make_tuple( 0.0, 1.0, 1.0 ) ); // cyan
    colorCodesVector.push_back( std::make_tuple( 0.576471, 0.858824, 0.439216 ) ); // green-yellow
    colorCodesVector.push_back( std::make_tuple( 0.737255, 0.560784, 0.560784 ) ); // pink
    colorCodesVector.push_back( std::make_tuple( 0.72, 0.45, 0.20 ) ); // copper
    colorCodesVector.push_back( std::make_tuple( 0.90, 0.91, 0.98 ) ); // silver
    colorCodesVector.push_back( std::make_tuple( 0.55, 0.09, 0.09 ) ); // scarlet

}





