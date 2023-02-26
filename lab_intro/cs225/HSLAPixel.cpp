/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225 {
    HSLAPixel::HSLAPixel(){
        h = 225.0;
        s = 0.5;
        l = 1.0;
        a = 1.0;
    }
    HSLAPixel::HSLAPixel(double hue, double saturation, double luminence){
        h = hue;
        s = saturation;
        l = luminence;
        a = 1.0;
    }
    HSLAPixel::HSLAPixel(double hue, double saturation, double luminence, double alpha){
        h = hue;
        s = saturation;
        l = luminence;
        a = alpha;
    }
}
