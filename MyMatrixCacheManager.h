//
// Created by arye on 23/01/2020.
//

#ifndef CLIENT_SERVER_COMMUNICATION__MYMATRIXCACHEMANAGER_H_
#define CLIENT_SERVER_COMMUNICATION__MYMATRIXCACHEMANAGER_H_

#include "CacheManager.h"
#include <iostream>
#include <map>
#include <fstream>
#include <unordered_map>
#include "CacheManager.h"

using namespace std;

class MyMatrixCacheManager : public CacheManager<string, string> {
 private:
  fstream matrix_cache_manager_stream;
  unordered_map<string, string> matrix_cache_manager_hash_map;
  string matrix_cache_manager_file_name;
 public:
  MyMatrixCacheManager(string & fileName){

    this->m_file_name = fileName;
    if (!fileExists(m_file_name)) {
      this->m_stream.open(m_file_name, ios::out);
      this->m_stream.close();
    }
    loadFromFile();
  }

  ~MyMatrixCacheManager() override;
  void insertSolution(string problem, string solution) override;
  string findSolution(string problem) override;
  void loadingFile() override;
  void writeToFile(string *problem, string *solution) override;
  bool isFileExists(string * fileName);
};

#endif //CLIENT_SERVER_COMMUNICATION__MYMATRIXCACHEMANAGER_H_
