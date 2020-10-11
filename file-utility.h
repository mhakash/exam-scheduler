#pragma once
#include<fstream>
#include<vector>

namespace ai {

  class FileUtility {
  private:
    std::string fileName;
    std::fstream fs;
  public:
    FileUtility(std::string filename);
    int getNextInt();
    bool hasNextLine();
    void write(std::string msg);
    void clearFile();
    std::vector<int> getNextLineInts();    
    ~FileUtility();
  };

} // namespace ai
