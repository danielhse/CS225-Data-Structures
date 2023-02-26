/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
   
    MosaicCanvas* canvas_ = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> pts;
    map<Point<3>, size_t> tiles; 
    
    for(size_t i = 0; i < theTiles.size(); i++){
      LUVAPixel pixel_ = theTiles[i].getAverageColor();
      Point<3> point = convertToXYZ(pixel_);
      pts.push_back(point);
      tiles.insert(pair<Point<3>, size_t>(point, i));
    }

    KDTree<3>* tree_ = new KDTree<3>(pts);

    for(int i = 0; i < theSource.getRows(); i++){
      for(int j = 0; j < theSource.getColumns(); j++){
        LUVAPixel color = theSource.getRegionColor(i, j);
        Point<3> point = convertToXYZ(color);
        Point<3> best = tree_->findNearestNeighbor(point);
        size_t idx = tiles[best];
        canvas_->setTile(i, j, &theTiles[idx]);
      }
    }
    
    return canvas_;
}

