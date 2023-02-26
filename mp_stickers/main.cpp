#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image alma;
  alma.readFromFile("alma.png");
  Image i;
  i.readFromFile("i.png");
  Image illinois;
  illinois.readFromFile("Illinois.png");

  StickerSheet sheet(alma, 100);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 674, 273);
  sheet.addSticker(illinois, 236, 120);
  sheet.translate(0, 0, 0);
  sheet.render().writeToFile("myImage.png");
  return 0;

}
