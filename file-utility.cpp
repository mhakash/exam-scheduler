#include "file-utility.h"
#include<sstream>

namespace ai {

  FileUtility::FileUtility(std::string fileName){
    this->fileName = fileName;
    fs.open ("../files/"+fileName, std::fstream::in | std::fstream::out | std::fstream::app);
  }

  FileUtility::~FileUtility(){
    fs.close();
  }

  std::vector<int> FileUtility::getNextLineInts(){
    std::vector<int> v;
    if(hasNextLine()){
      std::string line;
      getline(fs, line);
      std::istringstream is(line);

      int n;
      while (is >> n){
       v.push_back(n); 
      }
    }
    return v;
  }

  void FileUtility::write(std::string msg){
    fs << msg;    
  }

  void FileUtility::clearFile(){
    fs.close();
    std::ofstream ofs;
    ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    fs.open ("../files/"+fileName, std::fstream::in | std::fstream::out | std::fstream::app);
  }

  bool FileUtility::hasNextLine(){
    return fs.peek()!=EOF;
  }

  int FileUtility::getNextInt() {
    int a;
    fs >> a;
    return a;
  }

} // namespace ai
