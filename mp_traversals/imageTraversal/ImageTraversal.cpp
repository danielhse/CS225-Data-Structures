#include <cmath>
#include <iterator>
#include <iostream>
#include <list>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) 
    h = 360 - h; 
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  done = 1;
}

ImageTraversal::Iterator::Iterator(Point start, PNG png, double tolerance, ImageTraversal *traversal){
  start_ = start;
  curr = start;
  png_ = png;
  tolerance_ = tolerance;
  traversal_ = traversal;
  done = 0;
  for (unsigned i = 0; i < png.width() * png.height(); i++) {
    visited_.push_back(0);
  }
  if (start.x < 0 && start.x >= png_.width() && start.y < 0 && start.y >= png_.height()) 
    done = 1;
  else {
    if (calculateDelta(png_.getPixel(start_.x, start_.y), png_.getPixel(start.x, start.y)) < tolerance_) {
      visited_[start.x + start.y * png.width()] = 1;
      traversal->add(start);
    }
  }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

  Point right(curr.x + 1, curr.y);
  Point up(curr.x, curr.y + 1);
  Point left(curr.x - 1, curr.y);
  Point down(curr.x, curr.y - 1);

  if (right.x >= 0 && right.x < png_.width() && right.y >= 0 && right.y < png_.height()) {
    if (calculateDelta(png_.getPixel(start_.x, start_.y), png_.getPixel(right.x, right.y)) < tolerance_) {
      traversal_->add(right);
    }
  }
  if (up.x >= 0 && up.x < png_.width() && up.y >= 0 && up.y < png_.height()) {
    if (calculateDelta(png_.getPixel(start_.x, start_.y), png_.getPixel(up.x, up.y)) < tolerance_) {
      traversal_->add(up);
    }
  }
  if (left.x >= 0 && left.x < png_.width() && left.y >= 0 && left.y < png_.height()) {
    if (calculateDelta(png_.getPixel(start_.x, start_.y), png_.getPixel(left.x, left.y)) < tolerance_) {
      traversal_->add(left);
    }
  }
  if (down.x >= 0 && down.x < png_.width() && down.y >= 0 && down.y < png_.height()) {
    if (calculateDelta(png_.getPixel(start_.x, start_.y), png_.getPixel(down.x, down.y)) < tolerance_) {
      traversal_->add(down);
    }
  }

  if (traversal_->empty() != 1) {
    done = 0;
    curr = traversal_->pop();
    while (visited_[curr.x + (curr.y * png_.width())] == true){
      if (traversal_->empty() == true){
        done = 1;
        return *this;
      }
      curr = traversal_->pop();
    }
    visited_[curr.x + curr.y * png_.width()] = 1;
    return *this;

  } 
  else {
    done = 1;
    return *this;
  }
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return (done == other.done) == 0;
}