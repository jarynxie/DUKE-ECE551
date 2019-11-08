#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "set.h"
template<typename K>

class BstSet : public Set<K> {
 private:
  class Node {
   public:
    K key;
    Node * left;
    Node * right;
    Node() : left(NULL), right(NULL){};
    Node(const K & k) : key(k), left(NULL), right(NULL) {}
    Node(const K & k, Node * l, Node * r) : key(k), left(l), right(r) {}
  };
  Node * root;

 public:
  BstSet() : root(NULL) {}
  Node * copyHelper(const Node * node) {
    if (node == NULL) {
      return NULL;
    }
    Node * newNode = new Node(node->key);
    if (node->left != NULL) {
      newNode->left = copyHelper(node->left);
    }
    if (node->right != NULL) {
      newNode->right = copyHelper(node->right);
    }
    return newNode;
  }
  BstSet(const BstSet & rhs) { root = copyHelper(rhs.root); }
  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      //BstMap temp(rhs);
      //std::swap(root, temp.root);
      //destroy(temp.root);

      destroy(root);
      root = copyHelper(rhs.root);
    }
    return *this;
  }
  virtual void add(const K & key) {
    Node ** curr = &root;
    while (*curr != NULL) {
      if (key < (*curr)->key) {
        curr = &(*curr)->left;
      }
      else if (key > (*curr)->key) {
        curr = &(*curr)->right;
      }
    }
    *curr = new Node(key);
  }
  virtual bool contains(const K & key) const {
    Node * current = root;
    bool isFound = false;
    while (current != NULL) {
      if (key == current->key) {
        isFound = true;
        break;
      }
      else if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    return isFound;
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
        /*
        (*nodeToChange).key = (*curr)->key;
        (*nodeToChange).value = (*curr)->value;
        delete *curr;
        *curr = NULL;
	*/
        K tempkey = (*curr)->key;
        remove((*curr)->key);
        (*nodeToChange).key = tempkey;
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
  virtual ~BstSet<K>() { destroy(root); }
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
