// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template<typename T>
class TPQueue {
 private:
  struct Node {
    T value;
    Node* nextNode;
    explicit Node(const T& val) : value(val), nextNode(nullptr) {}
  };

  Node* front;
  Node* back;

 public:
  TPQueue() : front(nullptr), back(nullptr) {}

  ~TPQueue() {
    while (front) {
      Node* temp = front;
      front = front->nextNode;
      delete temp;
    }
  }

  void push(const T& item) {
    Node* node = new Node(item);

    if (!front || item.prior > front->value.prior) {
      node->nextNode = front;
      front = node;
      if (!back) {
        back = front;
    }
    return;
    }

    Node* cur = front;
    while (cur->nextNode &&
           cur->nextNode->value.prior >= item.prior) {
      cur = cur->nextNode;
    }

    node->nextNode = cur->nextNode;
    cur->nextNode = node;

    if (!node->nextNode) {
      back = node;
    }
  }

  T pop() {
    if (!front) {
      throw std::runtime_error("Очередь пуста!");
    }

    Node* temp = front;
    T result = front->value;
    front = front->nextNode;
    if (!front) {
      back = nullptr;
  }
    delete temp;
    return result;
  }

  bool empty() const {
    return front == nullptr;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
