/**
 * \author George Brown
 *
 * \file  Walls.hpp
 * \brief Class declaration for the walls which wrap around the perimeter of the window.
 *
 */

#ifndef WALLS_HPP
#define WALLS_HPP

/*! Walls class, which is used to form a collision boundary around the perimeter of the window */
class Walls {

    public:
    
        /*! The constructor for the Walls class takes two parameters: 
         *  appHeight and appWidth.
         * \param appHeight The height of the Walls of the window in pixels.
         * \param appWidth The width of the Walls of the window in pixels.
         */
        Walls(int appWidth, int appHeight);


        /*! Wall destructor. */
        ~Walls();


        /*! Returns the width of the wall in pixels. */
        int getWidth() const;


        /*! Returns the height of the wall in pixels. */
        int getHeight() const;


        /*! Returns the thickness of the wall in pixels. */
        int getThickness() const;

    private:
    
        /*! The width of the wall in pixels. */
        int width;

        /*! The height of the wall in pixels. */
        int height;

        /*! The thickness of the wall in pixels. */
        int thickness;
};

#endif
