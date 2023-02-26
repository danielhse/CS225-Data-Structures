#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>

using namespace cs225;
void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG in_image;
  in_image.readFromFile(inputFile);
  unsigned int width = in_image.width();
  unsigned int height = in_image.height();
  cs225::PNG out_image(width, height);
  for (unsigned int x = 0; x < in_image.width(); x++){
    for (unsigned int y = 0; y < in_image.height(); y++){
      HSLAPixel& in_pixel = in_image.getPixel(x, y);
      HSLAPixel& out_pixel = out_image.getPixel(width - (1 + x), height - (1 + y));
      out_pixel = in_pixel;
    }
  }
  out_image.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
 double hue = 143.0;
 double saturation = 0.19;
 double luminence = 0.56;
 for (unsigned int x = 0; x < width; x++){
    for (unsigned int y = 0; y < height; y++){
        HSLAPixel& pixel = png.getPixel(x, y);
        HSLAPixel art(hue, saturation, luminence);
        if (saturation == 0.8)
          saturation--;
        else
          saturation++;
        if (hue != 208.0)
          hue+=25;
           if (hue == 360)
            hue = 0.0;
        else
          hue-=10;
        pixel = art;
    }
 }
  return png;
}