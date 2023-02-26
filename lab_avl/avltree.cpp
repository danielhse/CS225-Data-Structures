/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
using namespace std;

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * small = t;
    Node * big = t->right; 
    t->right = t->right->left;
    big->left = t;
    t = big;
    newHeight(small);
    newHeight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * small = t->left; 
    Node * big = t;
    t->left = t->left->right;
    small->right = t;
    t = small;
    newHeight(big);
    newHeight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if (balance == 2) {
        int r_balance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if (r_balance != 1) {
            rotateRightLeft(subtree);
        } else {
            rotateLeft(subtree);
        }
    }
    if (balance == -2) {
        int l_balance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if (l_balance != -1) {
            rotateLeftRight(subtree);
        } else {
            rotateRight(subtree);
        }
    }
    newHeight(subtree);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
        subtree = new Node(key, value);
    } 
    if (key < subtree->key) {
        insert(subtree->left, key, value);
    } 
    if (key > subtree->key) {
        insert(subtree->right, key, value);
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            subtree = NULL;
            clear(subtree);
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node * change = subtree->left;
            Node * tmp;
            while(change->right) {
                tmp = change;
                change = change->right;
            }
            swap(subtree, change);
            clear(change);
            tmp->right = NULL;
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            if (subtree->left != NULL) {
                swap(subtree, subtree->left);
                clear(subtree->left);
                subtree->left = NULL;
            }
            if (subtree->right != NULL) {
                swap(subtree, subtree->right);
                clear(subtree->right);
                subtree->right = NULL;
            }
        }
        // your code here
    }
}

template <class K, class V>
void AVLTree<K, V>::newHeight(Node*& temp) {
    temp->height = 1 + fmax(heightOrNeg1(temp->left), heightOrNeg1(temp->right));
}