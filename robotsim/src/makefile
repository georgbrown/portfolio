UNAME = $(shell uname)

CC 		= g++
CFLAGS 	= -Wall  -std=c++14 #-m64
LDFLAGS =

##
# List of cpp files to be compiled
# Note, if you add any cpp files to your project, you must also add them here
##
CPPFILES += main.cpp 
CPPFILES += Walls.cpp
CPPFILES += BaseGfxApp.cpp 
CPPFILES += Simulation.cpp
CPPFILES += Obstacle.cpp
CPPFILES += Robot.cpp
CPPFILES += Target.cpp
CPPFILES += Environment.cpp
CPPFILES += BaseObject.cpp

##
# Lists all the cpp files in /src
# Note, this means you can make from /src, /lib, or /bin
##
SOURCES=$(addprefix ../src/,  $(CPPFILES))

OBJECTS = $(addprefix ../bin/,  $(CPPFILES:.cpp=.o)) 

GLUI = glui

##
# Linking the GLUI libraries
##
LINK_LIBS += -L../lib/$(GLUI)/lib/ -lglui
INCLUDE = -I../lib/$(GLUI)/include -I../src

##
# Linking GLUT and OpenGl for Mac
##
ifeq ($(UNAME), Darwin)
	LINK_LIBS += -framework glut -framework opengl
	EXECUTABLE = ../bin/gorobot
##
# Linking GLUT and OpenGl for Linux
##
else
	ifeq ($(UNAME), Linux)
		LINK_LIBS += -lglut -lGL -lGLU -L /usr/lib/nvidia-367
		EXECUTABLE = ../bin/gorobot
##
# Linking GLUT and OpenGl for Windows
# Note, you must have freeGlut installed; see the Resource page for details
##
	else 
		GLUTINCLUDEPATH = C:\Dev-Cpp\mingw32\freeglut\include\
		GLUTLIBPATH = C:\Dev-Cpp\mingw32\freeglut\lib\
		LINK_LIBS += -L$(GLUTLIBPATH) -lfreeglut -lopengl32 -Wl,--subsystem,windows
		INCLUDE += -I$(GLUTPATH)
		EXECUTABLE = gorobot.exe

	endif
endif

##
# Sets up the /bin folder, checks for all cpp files, and compiles the executables
# NOTE I REMOVED testrobot from the end of make all temporarily!!
##
all: setup $(SOURCES) $(EXECUTABLE) 

setup:
	mkdir -p ../bin

gorobot: $(EXECUTABLE)


##
# This ends up looking just like the compilation command we used in Lab 02
##
$(EXECUTABLE): $(GLUI) $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) $(LINK_LIBS) -o $@

##
# This creates the object files in the /bin folder
##
../bin/%.o: ../src/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

##
# This rule serves as a command for running the unit tests (typing "make tests") will run the tests
##
tests: testrobot
	../bin/testrobot

##
# Aliases for CxxTest directory, cxxtestgen, and flags
##
CXXDIR = ../bin/cxxtest
CXXTEST = $(CXXDIR)/bin/cxxtestgen
CXXFLAGS = --error-printer --abort-on-fail --have-eh
CXXOBJECTS = ../bin/Walls.o ../bin/Simulation.o ../bin/BaseGfxApp.o ../bin/Robot.o ../bin/Obstacle.o ../bin/Target.o ../bin/BaseObject.o ../bin/Environment.o 

##
# This rule creates an executable to run the tests by linking test object files:
##
testrobot: test.cpp $(GLUI) $(CXXOBJECTS)
	$(CC) $(CFLAGS) $(INCLUDE) -I$(CXXDIR) -o ../bin/testrobot $(CXXOBJECTS) test.cpp $(LINK_LIBS)

##
# This rule calls cxxtest scripts to auto-generate .cpp files to run the user-defined tests
##
test.cpp: EnvironmentTests.h RobotTests.h
	$(CXXTEST) $(CXXFLAGS) -o test.cpp EnvironmentTests.h RobotTests.h
#AgentTests.h
##
# Removes all object files, executables, and test.cpp
##
clean:
	\rm -rf $(OBJECTS) $(EXECUTABLE) ../bin/testrobot test.cpp *~
	 $(MAKE)  -C ../lib/$(GLUI) clean

$(GLUI):
	$(MAKE) -C ../lib/$(GLUI) all


