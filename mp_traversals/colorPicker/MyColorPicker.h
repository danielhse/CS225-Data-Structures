#pragma once

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"
//#include "../cs225/PNG.h"
//#include <string>

//using namespace std;
using namespace cs225;

/**
 * A color picker class using your own color picking algorithm
 */
class MyColorPicker : public ColorPicker {
public:
  //MyColorPicker(string images);
  HSLAPixel getColor(unsigned x, unsigned y);

private:
  //PNG png1;
};
