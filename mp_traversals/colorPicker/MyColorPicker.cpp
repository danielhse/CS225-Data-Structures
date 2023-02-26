#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"
//#include "../cs225/PNG.h"
//#include <string>

using namespace cs225;
//using namespace std;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */

/*
MyColorPicker::MyColorPicker(string images){
  png1.readFromFile(images);
}
*/

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  double h = ((x + y) * 112) % 360;
  return HSLAPixel(h, 1, 0.6);
  /*
  HSLAPixel cur = png1.getPixel(x % png1.width(), y % png1.width());
  if (cur > .1) { 
  		cur = HSLAPixel(HSLAPixel(243, 1, 0.5));
  	}
  	return cur;
  */
}
