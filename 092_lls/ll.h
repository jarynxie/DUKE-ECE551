#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>

template<typename T>

class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * prev;
    Node * next;
    Node() : prev(NULL), next(NULL){};
    Node(T d) : data(d), prev(NULL), next(NULL){};
    Node(const T & d, Node * p, Node * n) : data(d), prev(p), next(n) {}
  };
  class notExist : std::exception {};
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}
  LinkedList(const LinkedList & rhs) {
    head = NULL;
    tail = NULL;
    size = 0;
    for (int i = 0; i < rhs.getSize(); i++) {
      addBack(rhs[i]);
    }
  }
  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      for (int i = 0; i < rhs.getSize(); i++) {
        addBack(rhs[i]);
      }
    }
    return *this;
  }

  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
    size = 0;
    tail = NULL;
  }
  void addFront(const T & item) {
    head = new Node(item, NULL, head);
    size++;
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
  }
  void addBack(const T & item) {
    tail = new Node(item, tail, NULL);
    size++;
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
  }
  bool remove(const T & item) {
    Node * curr = head;
    if (getSize() == 0) {
      return false;
    }
    if (getSize() == 1 && head->data == item) {
      delete head;
      head = NULL;
      tail = NULL;
      size = 0;
      return true;
    }
    if (item == curr->data) {
      Node * newHead = head->next;
      head->next->prev = NULL;
      delete head;
      head = newHead;
      size--;
      return true;
    }
    if (tail->data == item) {
      Node * newTail = tail->prev;
      tail->prev->next = NULL;
      delete tail;
      tail = newTail;
      size--;
      return true;
    }
    while (curr->next != NULL) {
      if (item == curr->data) {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        size--;
        return true;
      }
      curr = curr->next;
    }
    return false;
  }

  T & operator[](int index) {
    if (index < 0 || index > getSize() - 1) {
      throw notExist();
    }
    Node * curr = head;
    for (int i = index; i > 0; i--) {
      curr = curr->next;
    }
    return curr->data;
  }
  const T & operator[](int index) const {
    if (index < 0 || index > getSize() - 1) {
      throw notExist();
    }
    Node * curr = head;
    for (int i = index; i > 0; i--) {
      curr = curr->next;
    }
    return curr->data;
  }
  int find(const T & item) {
    Node * curr = head;
    int i = 0;
    while (curr != NULL) {
      if (curr->data == item) {
        return i;
      }
      curr = curr->next;
      i++;
    }
    return -1;
  }
  int getSize() const { return size; }
};
#endif
