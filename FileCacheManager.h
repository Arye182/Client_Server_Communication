//
// Created by miri on 21.1.2020.
//

#ifndef CLIENT_SERVER_COMMUNICATION__FILECACHEMANAGER_H_
#define CLIENT_SERVER_COMMUNICATION__FILECACHEMANAGER_H_
#include "CacheManager.h"
#include <string>
using namespace std;
template <typename Problem, typename Solution>
 class FileCacheManager:public CacheManager<Problem, Solution>{
 public:
  FileCacheManager(){}
  void insertSolution(Problem problem, Solution solution){}
  Solution findSolution(Problem problem) override {
    return "not found";
  }

};
#endif //CLIENT_SERVER_COMMUNICATION__FILECACHEMANAGER_H_
