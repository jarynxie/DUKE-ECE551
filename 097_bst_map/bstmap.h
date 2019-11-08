#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>

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
  Node * copyHelper(const Node * node) {
    if (node == NULL) {
      return NULL;
    }
    Node * newNode = new Node(node->key, node->value);
    if (node->left != NULL) {
      newNode->left = copyHelper(node->left);
    }
    if (node->right != NULL) {
      newNode->right = copyHelper(node->right);
    }
    return newNode;
  }
  BstMap(const BstMap & rhs) { root = copyHelper(rhs.root); }
  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      //BstMap temp(rhs);
      //std::swap(root, temp.root);
      //destroy(temp.root);

      destroy(root);
      root = copyHelper(rhs.root);
    }
    return *this;
  }
  virtual void add(const K & key, const V & value) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if (key < (*curr)->key) {
        curr = &(*curr)->left;
      }
      else if (key > (*curr)->key) {
        curr = &(*curr)->right;
      }
      else {
        (*curr)->value = value;
        return;
      }
    }
    *curr = new Node(key, value);
  }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * current = root;
    //bool isFound = false;
    while (current != NULL) {
      if (key == current->key) {
        //isFound = true;
        //break;
        return current->value;
      }
      else if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    /*
    try {
      if (!isFound) {
        throw std::invalid_argument("Key not found!");
      }
    }
    catch (std::exception & e) {
      std::cerr << e.what() << std::endl;
    }
    return current->value;
    */
    throw std::invalid_argument("Key not found!");
  }
  virtual void remove(const K & key) {
    Node ** curr = &root;
    while (*curr != NULL && key != (*curr)->key) {
      if (key < (*curr)->key) {
        curr = &(*curr)->left;
      }
      else {
        curr = &(*curr)->right;
      }
    }
    if (*curr != NULL && (*curr)->left == NULL && (*curr)->right == NULL) {
      delete *curr;
      *curr = NULL;
    }
    else {
      if (*curr != NULL && (*curr)->left != NULL && (*curr)->right == NULL) {
        Node * temp = *curr;
        *curr = (*curr)->left;
        delete temp;
        temp = NULL;
      }
      else if (*curr != NULL && (*curr)->right != NULL && (*curr)->left == NULL) {
        Node * temp = *curr;
        *curr = (*curr)->right;
        delete temp;
        temp = NULL;
      }
      else if (*curr != NULL && (*curr)->right != NULL && (*curr)->left != NULL) {
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
  void printInOrder() {
    printHelper(root);
    std::cout << std::endl;
  }
};
