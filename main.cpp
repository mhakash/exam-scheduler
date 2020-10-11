#include "graph.h"
#include "node.h"
#include "file-utility.h"
#include "progress.h"
#include <iostream>
#include <fstream>

void solve(std::string fileNamePrefix);

unsigned int limit = 1000;

int main(int argc, char const* argv[]) {

  solve("car-s-91");
  solve("car-f-92");
  solve("kfu-s-93");
  solve("tre-s-92");
  solve("yor-f-83");

  return 0;
}

void solve(std::string fileNamePrefix){
  std::cout << "\n------- started ---- " << fileNamePrefix << "-------------------------------\n-\n";

  const std::string courseFileName = fileNamePrefix + ".crs";
  const std::string studentFileName = fileNamePrefix + ".stu";
  const std::string solutiontFileName = fileNamePrefix + ".sol";
  
  ai::Graph graph;
  graph.createNode(0, 0);
  
  ai::FileUtility course(courseFileName);
  while(course.hasNextLine()){
    auto t = course.getNextLineInts();
    graph.createNode(t[0], t[1]);
  }

  ai::FileUtility student(studentFileName);
  while(student.hasNextLine()){
    auto t = student.getNextLineInts();
    graph.stu.push_back(t);
    int l = static_cast<int>(t.size());
    for(int i=0; i<l-1; i++){
      for(int j=i+1; j<l; j++){
        graph.createEdge(t[i], t[j]);
      }
    }
  }

  graph.colorize();
  std::cout << "- total timeslots: " << graph.getColors() << '\n';
  std::cout << "- initial penaly: " << graph.getPenalty() << '\n';
  
  unsigned int width=70; 
  progresscpp::ProgressBar bar(limit, width);
  
  for(int i=0; i< static_cast<int>(limit); i++){
    graph.kempeChainInterChange();
    ++bar;
    //std::cout << "- current penalty: " << graph.getPenalty() <<" || ";
    std::cout.flush();
    bar.display();
  }
  bar.done();
  std::cout << "- final penalty: " << graph.getPenalty() <<"\n";
  std::cout << "-\n------------------- done ---------------------------------------\n\n";
  std::cout << std::endl;

  graph.generateSol(solutiontFileName);

}