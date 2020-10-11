#include "node.h"
#include <iostream>

namespace ai {

  Node::Node(){
    color = -1;
    weight = 0;
    dSatur = 0;
  }

  Node::~Node(){}

  void Node::setId(int id){
    this->id = id;
  }

  void Node::setWeight(int w){
    weight = w;
  }

  void Node::increamentdSatur(){
    dSatur++;
  }

  void Node::setColor(int color){
    this->color = color;
  }

  int Node::getColor(){
    return this->color;
  }

  int Node::getId(){
    return id;
  }

  int Node::getWeight(){
    return weight;
  }

  void Node::addNeighbour(Node* node) {
    neighbours.insert(node);
  } 

  int Node::getdSatur(){
    return dSatur;
  }

  bool Node::canColor(int color){
    bool flag = true;
    for(auto x: this->neighbours){
      if(x->getColor() == color) {
        flag = false;
        break;
      }
    }
    return flag;
  }

  void Node::printColor(){
    std::cout << this->color;
  }

  void Node::print() const{
    // std::cout << this->id << "(" << this->dSatur << "): ";
    std::cout << this->id << "(" << this->color << "): ";
    for(auto i:neighbours){
      std::cout << i->id << "(" << i->color << ") ";
      // std::cout << i->id << "(" << i->dSatur << ") ";
    }
  }

} // namespace ai
