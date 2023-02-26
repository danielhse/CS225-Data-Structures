/* Your code here! */
#include "dsets.h"

void DisjointSets::addelements(int num) {
    for (int i = 0; i <= num; i++) {
        trees.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    if (trees[elem] <= 0) {
        return elem;
    }
    return find(trees[elem]);
}

void DisjointSets::setunion(int a, int b) {
    int rootA = find(a);
    int rootB = find(b);
    if (rootA == rootB) 
        return;
    if (trees[rootA] <= trees[rootB]) {
        trees[rootA] += trees[rootB];
        trees[rootB] = rootA;
    } 
    else {
        trees[rootB] += trees[rootA];
        trees[rootA] = rootB;
    }
}

int DisjointSets::size(int elem) {
    elem = find(elem);
    return -1 * trees[elem];
}