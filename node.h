#pragma once
#include <set>

namespace ai {
  class Node {
  private:
    int id; 
    int color;
    int weight;
    int dSatur;
    // bool operator< (const Node &node) const;
  public:
    std::set<Node*> neighbours;
    Node();
    ~Node();
    int getColor();
    int getId();
    void printColor();
    void setWeight(int w);
    int getWeight();
    bool canColor(int color);
    void setId(int id);
    void setColor(int color);
    void increamentdSatur();
    int getdSatur();
    void addNeighbour(Node* node);
    void print() const;
  };
} // namespace ai
