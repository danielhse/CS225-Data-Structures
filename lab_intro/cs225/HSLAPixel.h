/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#pragma once

#include <iostream>
#include <sstream>

namespace cs225 {
    class HSLAPixel{
        public: 
            HSLAPixel();
            HSLAPixel(double hue, double saturation, double luminence);
            HSLAPixel(double hue, double saturation, double luminence, double alpha);
            double h;
            double l;
            double s;
            double a;
    };
}


