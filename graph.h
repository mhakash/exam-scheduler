#pragma once
#include <vector>
#include "node.h"
#include <unordered_map>

namespace ai {

  class Graph {
  private:
    int colors;
    int vertices;
    double penalty = 0;
    void kempe(Node* x, int c);
  public:
    Graph();
    std::vector<Node*> nodes;
    std::vector<std::vector<int>> stu;
    int getColors();
    void createNode(int id, int w);
    void createEdge(int u, int v);
    void generateSol(std::string fileName);
    void colorize();
    double getPenalty();
    void kempeChainInterChange();
    void printGraph();
    ~Graph();
  };
} // namespace ai
