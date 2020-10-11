#include "graph.h"
#include <iostream>
#include <queue>
#include <algorithm>
#include <random>
#include <fstream>

namespace ai {
  Graph::Graph(){
    this->colors = 0 ;
    this->vertices = 0;
    std::vector<int> t;
    stu.push_back(t);
  }
  Graph::~Graph(){}

  int Graph::getColors(){
    return this->colors;
  }

  void Graph::createNode(int id, int w){
    Node* node = new Node;
    node->setId(id);
    node->setWeight(w);
    nodes.push_back(node);
    this->vertices++;
  }

  void Graph::createEdge(int u, int v){
    nodes[u]->addNeighbour(nodes[v]);
    nodes[v]->addNeighbour(nodes[u]);
  }

  struct Compare {
    bool operator() (Node* x, Node* y){
      return x->getdSatur() < y->getdSatur(); // for larger first
    }
  };

  void Graph::colorize(){
    this->colors = 0;
    std::vector<bool> visited(vertices+1, false);
    
    int rnd = 1;
    nodes[rnd]->increamentdSatur();
    
    std::priority_queue<Node*, std::vector<Node*>, Compare> queue;
    for(auto x: nodes){
      queue.push(x);
    }

    while(!queue.empty()){
      auto t = queue.top();
      queue.pop();
      
      for(auto x: t->neighbours){
        int id = x->getId();
        if(!visited[id]){
          nodes[id]->increamentdSatur();
        }
      }

      int flag = -1;
      for(int i=1; i<this->colors; i++){
        if(t->canColor(i)){
          flag = i;
          break;
        }
      }
      if(flag == -1){
        this->colors ++;
        t->setColor(this->colors);
      }
      else{
        t->setColor(flag);
      }
      visited[t->getId()] = true;

      std::make_heap(
        const_cast<Node**>(&queue.top()), 
        const_cast<Node**>(&queue.top()) + queue.size(), 
        Compare()
      ); //update
    }
  }

  double Graph::getPenalty(){
    double penalty = 0;
    for(auto t: stu){;
      std::vector<int> x;
      for(auto p: t){
        x.push_back(nodes[p]->getColor());
      }
      std::sort(x.begin(), x.end());
      int l = x.size();
      for(int i=1; i<l; i++){
        int diff = x[i] - x[i-1];
        if(diff == 1) penalty += 16;
        else if(diff == 2) penalty += 8;
        else if(diff == 3) penalty += 4;
        else if(diff == 4) penalty += 2;
        else if(diff == 5) penalty += 1;
      }
    }
    penalty = penalty * 1.0;
    penalty = penalty / (stu.size() - 1);
    // std::cout << vertices << '\n';
    this->penalty = penalty;
    return penalty;
  }

  void Graph::kempeChainInterChange(){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1, vertices-1);
    int x = static_cast<int>(dist(mt));
    int nSize = nodes[x]->neighbours.size();
    std::uniform_real_distribution<double> dist2(0, nSize ? nSize - 1: 0);
    int y = static_cast<int>(dist2(mt));

    int color0 = nodes[x]->getColor();

    // std::cout << x <<" " << y << '\n';
    // std::cout << "d1\n";

    kempe(nodes[x], nSize ? nodes[y]->getColor() : nodes[x]->getColor()); 
    double penal1 = this->getPenalty();

    if(penal1 > this->penalty){
      kempe(nodes[x], color0);
    }
    else {
      this->penalty = penal1;
    }
    // std::cout << "penaly: " << this->getPenalty() << '\n';
  }

  void Graph::kempe(Node* x, int c){
    int t = x->getColor();
    x->setColor(c);
    for(auto p: x->neighbours){
      if(p->getColor() == c){
        kempe(p, t);
      }
    }
  }

  void Graph::generateSol(std::string fileName){
    std::fstream ofs;
    ofs.open("../files/"+ fileName,std::ofstream::out | std::ofstream::trunc);
    for(auto x: nodes){
      if(x->getId() == 0) continue;
      ofs << x->getId() << " " << x->getColor() <<  "\n";
    }
    ofs.close();
  }

  void Graph::printGraph(){
    for(auto i: nodes){
      i->print();
      std::cout << std::endl;
    }
  }

} 