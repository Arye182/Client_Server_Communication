//
// Created by arye on 23/01/2020.
//

#ifndef CLIENT_SERVER_COMMUNICATION__MYMATRIXCACHEMANAGER_H_
#define CLIENT_SERVER_COMMUNICATION__MYMATRIXCACHEMANAGER_H_

#include "CacheManager.h"
#include <iostream>
#include <map>
#include <fstream>
#include <mutex>

using namespace std;
static mutex lock_cache;
class MyMatrixCacheManager : public CacheManager<string, string> {
 private:
  hash < string > hasher;

 public:
  MyMatrixCacheManager() = default;
  //~MyMatrixCacheManager() override = default;
  void insertSolution(string problem, string solution) override;
  string findSolution(string problem) override;
};

#endif //CLIENT_SERVER_COMMUNICATION__MYMATRIXCACHEMANAGER_H_
