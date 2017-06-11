#include "Walls.hpp"

Walls::Walls(int appWidth, int appHeight){
    width = appWidth;
    height = appHeight;
    thickness = appWidth / 50;
}


Walls::~Walls(){
}


int Walls::getWidth() const {
    return width;
}


int Walls::getHeight() const {
    return height;
}


int Walls::getThickness() const {
    return thickness;
}





