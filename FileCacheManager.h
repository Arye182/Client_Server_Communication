//
// Created by miri on 21.1.2020.
//

#ifndef CLIENT_SERVER_COMMUNICATION__FILECACHEMANAGER_H_
#define CLIENT_SERVER_COMMUNICATION__FILECACHEMANAGER_H_
#include "CacheManager.h"
#include <string>
using namespace std;

 class FileCacheManager:public CacheManager<string, string>{
 public:
  FileCacheManager(){}
  void insertSolution(string problem, string solution){}
  string findSolution(string problem) override {
    return "not found";
  }

};
#endif //CLIENT_SERVER_COMMUNICATION__FILECACHEMANAGER_H_
