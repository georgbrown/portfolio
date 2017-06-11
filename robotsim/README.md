# portfolio

This is a small code sample for a real-time graphical application written in C++. The code contains full 
documentation using Doxygen and unit testing with Cxxtest. 

INTRODUCTION:
=============

The application is a 2D robot simulator. Robots, depicted as simple circles in the app, seek out and
pursue targets which are assigned to them. The targets are constantly moving, so the robots are required
to recalculate the path to the target frequently. Additionally, obstacles are randomly scattered across
the environment which the robots must avoid when pursuing the targets.

DESIGN:
=======

OOP principles are extensively utilized in the design. A graphical application class, BaseGfxApp, is defined with
virtual methods for managing input and the graphical display. A Simulation class inherits from BaseGfxApp,
and implements the context for the graphical robot application. 

An instance of an Environment class is contained within the Simulation. The Environment is the physical domain
which all objects live and move around within. The BaseObject class is a parent template class which all variants
of objects inherit from. Robot, Target, and Obstacle classes all inherit from BaseObject and implement the
functionality described in the introduction.

For more details please consult the Doxygen documentation. 


COMPILING & RUNNING:
====================

(Currently only Linux is supported)

cd ./codesample/src
make
cd ..
bin/gorobot


