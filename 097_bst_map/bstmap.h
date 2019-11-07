#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "map.h"
template<typename K, typename V>

class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node() : left(NULL), right(NULL){};
    Node(const K & k, const V & v) : key(k), value(v), left(NULL), right(NULL) {}
    Node(const K & k, const V & v, Node * l, Node * r) :
        key(k),
        value(v),
        left(l),
        right(r) {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap & rhs) { rhs.root = NULL; }
  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      BstMap temp(rhs);
      std::swap(temp.root, root);
    }
    return *this;
  }
  Node * addHelper(Node * current, const K & key, const V & value) {
    if (current == NULL) {
      Node * ans = new Node(key, value);
      return ans;
    }
    else {
      if (key == current->key) {
        current->value = value;
      }
      else {
        if (key < current->key) {
          Node * newLeft = addHelper(current->left, key, value);
          current->left = newLeft;
        }
        else {
          Node * newRight = addHelper(current->right, key, value);
          current->right = newRight;
        }
      }
      return current;
    }
  }

  virtual void add(const K & key, const V & value) { root = addHelper(root, key, value); }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * current = root;
    while (current != NULL) {
      if (key == current->key) {
        return current->value;
      }
      else if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    throw std::invalid_argument("Key not found!");
  }
  virtual void remove(const K & key) {
    Node ** curr = &root;
    while ((*curr)->key != key) {
      if (key < (*curr)->key) {
        curr = &(*curr)->left;
      }
      else {
        curr = &(*curr)->right;
      }
    }
    if ((*curr)->left == NULL && (*curr)->right == NULL) {
      delete *curr;
      *curr = NULL;
    }
    else {
      if ((*curr)->left != NULL && (*curr)->right == NULL) {
        Node * temp = *curr;
        *curr = (*curr)->left;
        delete temp;
        temp = NULL;
      }
      else if ((*curr)->right != NULL && (*curr)->left == NULL) {
        Node * temp = *curr;
        *curr = (*curr)->right;
        delete temp;
        temp = NULL;
      }
      else if ((*curr)->right != NULL && (*curr)->left != NULL) {
        Node * nodeToChange = *curr;
        curr = &(*curr)->right;
        while ((*curr)->left != NULL) {
          curr = &(*curr)->left;
        }
        (*nodeToChange).key = (*curr)->key;
        (*nodeToChange).value = (*curr)->value;
        delete *curr;
        *curr = NULL;
      }
    }
  }

  void destroy(Node * current) {
    if (current != NULL) {
      destroy(current->left);
      destroy(current->right);
      delete current;
    }
  }
  virtual ~BstMap<K, V>() { destroy(root); }
  void printHelper(Node * current) {
    if (current != NULL) {
      printHelper(current->left);
      std::cout << current->key << " ";
      printHelper(current->right);
    }
  }
  void printInOrder() { printHelper(root); }
};
