/**
 * \author CSci5107 Instructor
 *
 * \file  main.cpp
 * \brief Main function.
 *
 */

#include "Simulation.hpp"
#include <ctime>

int main(int argc, char* argv[])
{
    // Setting the random seed which is used for calls to rand()
    srand( time( NULL ) );

    Simulation *app = new Simulation(argc, argv,800,800);

    app->runMainLoop();
    exit(0);
}

