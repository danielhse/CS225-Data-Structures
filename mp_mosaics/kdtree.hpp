/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim] < second[curDim])
      return 1;
    if(first[curDim] == second[curDim])
      return first < second;
    else
      return 0;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    
    float cur = 0.0;
    float ptl = 0.0;

    for(int i = 0; i < Dim; i++){
      cur = cur + (currentBest[i] - target[i]) * (currentBest[i] - target[i]);
    }
    for(int i = 0; i < Dim; i++){
      ptl = ptl + (target[i] - potential[i]) * (target[i] - potential[i]);
    }

    if(ptl < cur)
      return 1;
    if(ptl == cur)
      return potential < currentBest;
    else 
      return 0;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if(!newPoints.empty()){
      vector<Point<Dim>> pts = newPoints;
      size = 0;
      helperKD(pts, 0, pts.size() - 1, 0, root);
    }
    else{
      size = 0;
      root = NULL; 
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copy_(root, other->root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  copy_(root, rhs->root);
  delete_(root);
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  delete_(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> new_ = query; 
    Point<Dim> curr_ = root->point;
    findtheNearestNeighbor(root, curr_, new_, 0);
    return curr_;
}


template <int Dim>
void KDTree<Dim>::findtheNearestNeighbor(KDTreeNode* curr_node, Point<Dim> &currentBest,
                         Point<Dim> &query, int dimension) const{
    
    if(curr_node == NULL)
      return;

    KDTreeNode* next;
    KDTreeNode* other;

    if(!smallerDimVal(curr_node->point, query, dimension)){
      next = curr_node->left;
      other = curr_node->right;
    }
    else{
      next = curr_node->right;
      other = curr_node->left;
    }

    findtheNearestNeighbor(next, currentBest, query, (dimension + 1) % Dim);

    if(shouldReplace(query, currentBest, curr_node->point)){
      currentBest = curr_node->point;
    }

    float dis =  (curr_node->point[dimension] - query[dimension])
                    * (curr_node->point[dimension] - query[dimension]);
    float rad = 0.0;

    for(int i = 0; i < Dim; i++){
      rad = rad + (currentBest[i] - query[i]) * (currentBest[i] - query[i]);
    }   

    if(dis <= rad)
      findtheNearestNeighbor(other, currentBest, query, (dimension + 1) % Dim);
}

template <int Dim>
void KDTree<Dim>::helperKD(vector<Point<Dim>>& newPoints, int left, int right,
                              int dimension, KDTreeNode*& subroot){
  if(left > right)
    return;
  
  size_t avg = (left + right) / 2;

  Point<Dim> temp_ = select(newPoints, left, right, avg, dimension);
  subroot = new KDTreeNode(temp_);
  size = size + 1;

  helperKD(newPoints, left, avg - 1, (dimension + 1) % Dim, subroot->left);
  helperKD(newPoints, avg + 1, right, (dimension + 1) % Dim, subroot->right);
}

template <int Dim>
int KDTree<Dim>::part(vector<Point<Dim>>& list, int left, int right, size_t Idx, int dimension){
  Point<Dim> pvt = list[Idx];
  swap(list[Idx], list[right]);  
  size_t storeIdx = left;
  for(int i = left; i < right; i++){
    if(smallerDimVal(list[i], pvt, dimension) == 1){
      swap(list[storeIdx], list[i]);
      storeIdx = storeIdx + 1;
    }
  }
  swap(list[right], list[storeIdx]);  
  return storeIdx;
}

template <int Dim>
Point<Dim> KDTree<Dim>::select(vector<Point<Dim>>& list, int left, int right, size_t k, int dimension){
  size_t pivotIdx = (left + right) / 2;    // select a pivotIndex between left and right
  pivotIdx = part(list, left, right, pivotIdx, dimension);
  
  if(k < pivotIdx)
    return select(list, left, pivotIdx - 1, k, dimension);
  if (k > pivotIdx)
    return select(list, pivotIdx + 1, right, k, dimension);  
  else
    return list[k];

  if(left == right)    
    return list[left]; 
}

template <int Dim>
void KDTree<Dim>::copy_(KDTreeNode*& curr_node, KDTreeNode*& other){
  curr_node = new KDTreeNode(other->point);
  copy_(curr_node->left, other->left);
  copy_(curr_node->right, other->right);

  if(other == NULL)
    return;
}

template <int Dim>
void KDTree<Dim>::delete_(KDTreeNode*& subroot){
  if(subroot == NULL)
    return;
  delete_(subroot->left);
  delete_(subroot->right);
}
