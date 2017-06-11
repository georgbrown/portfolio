/**
 * \author CSci3081 Instructor, George Brown
 *
 * \file  BaseGfxApp.hpp
 * \brief The basic application class for CSci-3081 project.  Uses GLUT and 
 *        GLUI and wraps them in a nice C++ interface.
 *
 */

#ifndef BASEGFXAPP_HPP
#define BASEGFXAPP_HPP

// Frequently used C++ stuff 
#include <string>
#include <iostream>
using namespace std;
#include <assert.h>

// The GLUI library, which in turn will include gl.h and glut.h
#include "../lib/glui/include/GL/glui.h"

class BaseGfxApp {

    public:

        /*! Constructor which sets up the graphical application
         * \param argc Command line argument count
         * \param argv Command line arguments
         * \param width Width of the graphical window
         * \param height Height of the graphical window
         * \param x The reference x position for the graphical window
         * \param y The reference y position for the graphical window
         * \param glutFlags Additional flags used by GLUT system
         * \param createGLUIWin Flag which determines whether a GLUI interface window should be created
         * \param gluiWinX GLUI interface reference x position
         * \param gluiWinY GLUI interface reference y position */
        BaseGfxApp(int argc, char* argv[], int width, int height, int x, int y, int glutFlags, 
                bool createGLUIWin, int gluiWinX, int gluiWinY);
        
                
        /*! Virtual graphical application destructor which may be overridden by inheriting classes */
        virtual ~BaseGfxApp();


        /*! Sets a caption for the graphical application window 
         * \param caption A string object which will be displayed as the caption for this application */
        void setCaption(const std::string& caption);

        
        /*! Main loop driver function */
        void runMainLoop();


        /*! Virtual display function which is called every time the application window is refreshed */
        virtual void display() {};
    
        
        /*! Response to mouse movement events
         * \param x The mouse x position
         * \param y The mouse y position */
        virtual void mouseMoved(int x, int y) {};
        
        
        /*! Response to mouse dragging events 
         * \param x The mouse x position
         * \param y The mouse y position */
        virtual void mouseDragged(int x, int y) {};


        /*! Response to an event in which the left mouse button is pressed down
         * \param x The mouse x position
         * \param y The mouse y position */
        virtual void leftMouseDown(int x, int y) {};
        
        
        /*! Response to an event in which the left mouse button is released from previously being down
         * \param x The mouse x position
         * \param y The mouse y position */
        virtual void leftMouseUp(int x, int y) {};
        
        
        /*! Response to an event in which the right mouse button is pressed down
         * \param x The mouse x position
         * \param y The mouse y position */
        virtual void rightMouseDown(int x, int y) {};
        
        
        /*! Response to an event in which the right mouse button is released from previously being down
         * \param x The mouse x position
         * \param y The mouse y position */
        virtual void rightMouseUp(int x, int y) {};
        
        
        /*! Response to an event in which the middle mouse button is pressed down
         * \param x The mouse x position
         * \param y The mouse y position */
        virtual void middleMouseDown(int x, int y) {};
        
        
        /*! Response to an event in which the middle mouse button is released from previously being down
         * \param x The mouse x position
         * \param y The mouse y position */
        virtual void middleMouseUp(int x, int y) {};
    
    
        /*! Response to an event in which a key on the keyboard is pressed
         * \param c The character value associated with the pressed key
         * \param x The mouse x position
         * \param y The mouse y position */
        virtual void keyboard(unsigned char c, int x, int y) {};
        
        
        /*! Response to an event in which a special key on the keyboard is pressed
         * \param key The special key code corresponding to the button pressed 
         * \param x The mouse x position
         * \param y The mouse y position */
        virtual void keyboardSpecial(int key, int x, int y) {};
        
        
        /*! Response to an event in which a key on the keyboard is released from previously being down
         * \param c The character value associated with the pressed key
         * \param x The mouse x position
         * \param y The mouse y position */
        virtual void keyboardUp(unsigned char c, int x, int y) {};
        
        
        /*! Response to an event in which a special key on the keyboard is released from previously being down
         * \param key The special key code corresponding to the button released
         * \param x The mouse x position
         * \param y The mouse y position */
        virtual void keyboardSpecialUp(int key, int x, int y) {};
        
        
        /*! Response to the graphical window being resized at runtime 
         * \param width The new window width
         * \param height The new window height */
        virtual void reshape(int width, int height);


        /*! Response to a glui control command 
         * \param controlID The ID of the glui control */
        virtual void gluiControl(int controlID) {};


        /*! Returns the graphical window width (in pixels) */
        int width() const;
        

        /*! Returns the graphical window height (in pixels) */
        int height() const;
        
        
        /*! Wrapper which gets the GLUT window handle */
        int handle() { return m_glutWindowHandle; }
        
        
        /*! Wrapper which returns the GLUI instance */
        GLUI* glui() { return m_glui; }


    protected:

        /** GLUT and GLUI event callbacks are sent to the current window/app. Right now, there is only
            one window anyway (not counting the GLUI UI window.. in the future could be extended to 
            support more windows.  In any case, some structure like this is always needed when using 
            glut with C++, since the glut callbacks must be either global or static functions. */
        static BaseGfxApp* s_currentApp;  

        /** Has glutInit been called? (only allowed once per program) */
        static bool    s_glutInitialized;

        // Glut callbacks:
        static void s_reshape(int width, int height);
        static void s_keyboard(unsigned char c, int x, int y);
        static void s_keyboardspecial(int key, int x, int y);
        static void s_keyboardup(unsigned char c, int x, int y);
        static void s_keyboardspecialup(int key, int x, int y);
        static void s_mousemotion(int x, int y);
        static void s_mousebtn(int b, int s, int x, int y);
        static void s_draw();    
        static void s_gluicallback(int controlID);

        /** Underlying glut window handle */
        int m_glutWindowHandle;

        // Pointer to GLUI master
        GLUI* m_glui;

        bool m_drag;
        int m_width;
        int m_height;
};


#endif
